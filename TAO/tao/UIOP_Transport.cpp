// This may look like C, but it's really -*- C++ -*-
// $Id$

# if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)

#include "tao/UIOP_Transport.h"
#include "tao/UIOP_Connect.h"
#include "tao/Timeprobe.h"
#include "tao/CDR.h"
#include "tao/Transport_Mux_Strategy.h"
#include "tao/Wait_Strategy.h"
#include "tao/Reply_Dispatcher.h"
#include "tao/ORB_Core.h"
#include "tao/debug.h"

#if defined (ACE_ENABLE_TIMEPROBES)

static const char *TAO_Transport_Timeprobe_Description[] =
  {
    "UIOP_Transport::send - start",
    "UIOP_Transport::send - end",

    "UIOP_Transport::receive - start",
    "UIOP_Transport::recieve - end",

    "UIOP_Client_Transport::send_request - start",
    "UIOP_Client_Transport::send_request - end"
  };

enum
  {
    TAO_UIOP_TRANSPORT_SEND_START = 1200,
    TAO_UIOP_TRANSPORT_SEND_END,

    TAO_UIOP_TRANSPORT_RECEIVE_START,
    TAO_UIOP_TRANSPORT_RECEIVE_END,

    TAO_UIOP_CLIENT_TRANSPORT_SEND_REQUEST_START,
    TAO_UIOP_CLIENT_TRANSPORT_SEND_REQUEST_END
  };


// Setup Timeprobes
ACE_TIMEPROBE_EVENT_DESCRIPTIONS (TAO_Transport_Timeprobe_Description,
                                  TAO_UIOP_TRANSPORT_SEND_START);

#endif /* ACE_ENABLE_TIMEPROBES */

TAO_UIOP_Transport::TAO_UIOP_Transport (TAO_UIOP_Handler_Base *handler,
                                        TAO_ORB_Core *orb_core)
  : TAO_Transport (TAO_IOP_TAG_UNIX_IOP,
                   orb_core),
    handler_ (handler)
{
}

TAO_UIOP_Transport::~TAO_UIOP_Transport (void)
{
}

TAO_UIOP_Server_Transport::
    TAO_UIOP_Server_Transport (TAO_UIOP_Server_Connection_Handler *handler,
                               TAO_ORB_Core* orb_core)
  : TAO_UIOP_Transport (handler, orb_core),
    server_handler_ (handler)
{
}

TAO_UIOP_Client_Transport::
    TAO_UIOP_Client_Transport (TAO_UIOP_Client_Connection_Handler *handler,
                               TAO_ORB_Core *orb_core)
  :  TAO_UIOP_Transport (handler,
                         orb_core),
     client_handler_ (handler)
{
}

TAO_UIOP_Server_Transport::~TAO_UIOP_Server_Transport (void)
{
}

TAO_UIOP_Client_Transport::~TAO_UIOP_Client_Transport (void)
{
}

TAO_UIOP_Client_Connection_Handler *
TAO_UIOP_Client_Transport::client_handler (void)
{
  return this->client_handler_;
}

TAO_UIOP_Server_Connection_Handler *
TAO_UIOP_Server_Transport::server_handler (void)
{
  return this->server_handler_;
}

TAO_UIOP_Handler_Base *&
TAO_UIOP_Transport::handler (void)
{
  return this->handler_;
}

int
TAO_UIOP_Transport::idle (void)
{
  return this->handler_->idle();
}

void
TAO_UIOP_Transport::close_connection (void)
{
  this->handler_->handle_close ();
}

ACE_HANDLE
TAO_UIOP_Transport::handle (void)
{
  return this->handler_->get_handle ();
}

int
TAO_UIOP_Client_Transport::send_request (TAO_ORB_Core *orb_core,
                                         TAO_OutputCDR &stream,
                                         int two_way)
{
  ACE_FUNCTION_TIMEPROBE (TAO_UIOP_CLIENT_TRANSPORT_SEND_REQUEST_START);

  if (this->ws_->sending_request (orb_core,
                                  two_way) == -1)
    return -1;

  return TAO_GIOP::send_message (this,
                                 stream,
                                 orb_core);
}

// Return 0, when the reply is not read fully, 1 if it is read fully.
// @@ This code should go in the TAO_Transport class is repeated for
//    each transport!!
int
TAO_UIOP_Client_Transport::handle_client_input (int block)
{
  // When we multiplex several invocations over a connection we need
  // to allocate the CDR stream *here*, but when there is a single
  // request over a connection the CDR stream can be pre-allocated on
  // the stack of the thread that sent the request!
  // Can we preserve this optimization on the new architecture?
  //
  // here is how:
  //
  // Use an "factory" to obtain the CDR stream, in the Muxed case the
  // factory simply allocates a new one, in the Exclusive case the
  // factory returns a pointer to the pre-allocated CDR.
  //
  // @@ Alex: I thought some more about this, and here is how i would
  //    like to do it: this class keeps a CDR stream for the "current"
  //    message beign received. Initially the CDR is 0, when the
  //    handle_client_input() is called the first time then we go to
  //    the muxer to obtain the CDR stream.
  //    - The exclusive Muxer returns the CDR stream pre-allocated by
  //      the invocation.
  //    - The shared Muxer returns a new CDR stream.
  //    Once all the data has been received the reply handler takes
  //    charge of the CDR stream, or actually of its message block,
  //    which is referenced counted and thus can be efficiently
  //    removed.
  //    Do I make any sense?

  TAO_InputCDR* cdr = this->tms_->get_cdr_stream ();
  ACE_Message_Block* payload =
    ACE_const_cast(ACE_Message_Block*, cdr->start ());

  int result = TAO_GIOP::handle_input (this,
                                       this->orb_core_,
                                       this->message_header_,
                                       this->current_offset_,
                                       payload);
  if (result == -1)
    {
      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG,
                    "TAO (%P|%t) - %p\n",
                    "UIOP_Transport::handle_client_input, handle_input"));
      return -1;
    }
  if (result == 0)
    return result;

  // OK, the complete message is here...

  TAO_GIOP_MessageHeader header_copy = this->message_header_;
  this->message_header_.message_size = 0;

  TAO_GIOP_ServiceContextList reply_ctx;
  CORBA::ULong request_id;
  CORBA::ULong reply_status;

  result = TAO_GIOP::parse_reply (this,
                                  this->orb_core_,
                                  *cdr,
                                  header_copy,
                                  reply_ctx,
                                  request_id,
                                  reply_status);
  if (result == -1)
    {
      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG,
                    "TAO (%P|%t) - %p\n",
                    "UIOP_Transport::handle_client_input, parse reply"));
      return -1;
    }

  if (this->tms_->dispatch_reply (request_id,
                                  reply_status,
                                  header_copy.giop_version,
                                  reply_ctx,
                                  cdr) != 0)
    {
      if (TAO_debug_level > 0)
        ACE_ERROR ((LM_ERROR,
                    "TAO (%P|%t) : UIOP_Client_Transport::"
                    "handle_client_input - "
                    "dispatch reply failed\n"));
      return -1;
    }

  // This is a NOOP for the Exclusive request case, but it actually
  // destroys the stream in the muxed case.
  this->destroy_cdr_stream (cdr);

  // Return something to indicate the reply is received.
  return 1;
}

int
TAO_UIOP_Client_Transport::register_handler (void)
{
  ACE_Reactor *r = this->orb_core ()->reactor ();
  if (r == this->client_handler ()->reactor ())
    return 0;

  return r->register_handler (this->client_handler (),
                              ACE_Event_Handler::READ_MASK);
}

int
TAO_UIOP_Client_Transport::check_unexpected_data (void)
{
  // @@ Alex: This should *not* be part of the client connection
  //    handler, we should treat any incoming data as a GIOP message.
  //    The server can always send the "CloseConnection" message and
  //    we should act accordingly.
  //    Finally: in the future the server may send requests though
  //    GIOP 1.2 connections, we shouldn't hard-code the current GIOP
  //    state machine at this level...

  // We're a client, so we're not expecting to see input.  Still we
  // better check what it is!
  char ignored;
  ssize_t ret = this->client_handler ()->peer().recv (&ignored,
                                                      sizeof ignored,
                                                      MSG_PEEK);
  switch (ret)
    {
    case 0:
    case -1:
      // 0 is a graceful shutdown
      // -1 is a somewhat ugly shutdown
      //
      // Both will result in us returning -1 and this connection
      // getting closed
      //
      // if (errno == EWOULDBLOCK)
      // return 0;

      if (TAO_debug_level)
        ACE_DEBUG ((LM_WARNING,
                    "TAO_UIOP_Client_Transport::check_unexpected_data: "
                    "closing connection on fd %d\n",
                    this->client_handler ()->peer().get_handle ()));
      break;

    case 1:
      //
      // @@ Fix me!!
      //
      // This should be the close connection message.  Since we don't
      // handle this yet, log an error, and close the connection.
      ACE_ERROR ((LM_WARNING,
                  "TAO_UIOP_Client_Transport::check_unexpected_data: "
                  "input while not expecting a response; "
                  "closing connection on fd %d\n",
                  this->client_handler ()->peer().get_handle ()));
      break;
    }

  // We're not expecting input at this time, so we'll always
  // return -1 for now.
  return -1;
}

// ****************************************************************

ssize_t
TAO_UIOP_Transport::send (const ACE_Message_Block *mblk, ACE_Time_Value *)
{
  TAO_FUNCTION_PP_TIMEPROBE (TAO_UIOP_TRANSPORT_SEND_START);

  // For the most part this was copied from GIOP::send_request and
  // friends.

  iovec iov[IOV_MAX];
  int iovcnt = 0;
  ssize_t n = 0;
  ssize_t nbytes = 0;

  for (const ACE_Message_Block *i = mblk;
       i != 0;
       i = i->cont ())
    {
      // Make sure there is something to send!
      if (i->length () > 0)
        {
          iov[iovcnt].iov_base = i->rd_ptr ();
          iov[iovcnt].iov_len  = i->length ();
          iovcnt++;

          // The buffer is full make a OS call.  @@ TODO this should
          // be optimized on a per-platform basis, for instance, some
          // platforms do not implement writev() there we should copy
          // the data into a buffer and call send_n(). In other cases
          // there may be some limits on the size of the iovec, there
          // we should set IOV_MAX to that limit.
          if (iovcnt == IOV_MAX)
            {
              n = this->handler_->peer ().sendv_n ((const iovec *) iov,
                                                   iovcnt);
              if (n < 1)
                return n;

              nbytes += n;
              iovcnt = 0;
            }
        }
    }

  // Check for remaining buffers to be sent!
  if (iovcnt != 0)
    {
      n = this->handler_->peer ().sendv_n ((const iovec *) iov,
                                           iovcnt);
      if (n < 1)
        return n;

      nbytes += n;
    }

  return nbytes;
}

ssize_t
TAO_UIOP_Transport::send (const u_char *buf,
                          size_t len,
                          ACE_Time_Value *)
{
  TAO_FUNCTION_PP_TIMEPROBE (TAO_UIOP_TRANSPORT_SEND_START);

  return this->handler_->peer ().send_n (buf, len);
}

ssize_t
TAO_UIOP_Transport::send (const iovec *iov,
                          int iovcnt,
                          ACE_Time_Value *)
{
  TAO_FUNCTION_PP_TIMEPROBE (TAO_UIOP_TRANSPORT_SEND_START);

  return this->handler_->peer ().sendv_n ((const iovec *) iov,
                                          iovcnt);
}

ssize_t
TAO_UIOP_Transport::recv (char *buf,
                          size_t len,
                          ACE_Time_Value *)
{
  TAO_FUNCTION_PP_TIMEPROBE (TAO_UIOP_TRANSPORT_RECEIVE_START);

  return this->handler_->peer ().recv_n (buf, len);
}

ssize_t
TAO_UIOP_Transport::recv (char *buf,
                          size_t len,
                          int flags,
                          ACE_Time_Value *)
{
  //  TAO_FUNCTION_PP_TIMEPROBE (TAO_UIOP_TRANSPORT_RECEIVE_START);

  return this->handler_->peer ().recv_n (buf,
                                         len,
                                         flags);
}

ssize_t
TAO_UIOP_Transport::recv (iovec *iov,
                          int iovcnt,
                          ACE_Time_Value *)
{
  //  TAO_FUNCTION_PP_TIMEPROBE (TAO_UIOP_TRANSPORT_RECEIVE_START);

  return handler_->peer ().recvv_n (iov, iovcnt);
}

// Default action to be taken for send request.
int
TAO_UIOP_Transport::send_request (TAO_ORB_Core *  /* orb_core */,
                                  TAO_OutputCDR & /* stream   */,
                                  int             /* twoway   */)
{
  return -1;
}

#endif  /* !ACE_LACKS_UNIX_DOMAIN_SOCKETS */
