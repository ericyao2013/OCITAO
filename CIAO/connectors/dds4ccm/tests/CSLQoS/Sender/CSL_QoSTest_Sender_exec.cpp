// -*- C++ -*-
// $Id$

//Test for ConnectorStatusListener: on_offered_incompatible_qos

#include "CSL_QoSTest_Sender_exec.h"
#include "ace/Guard_T.h"
#include "ace/Log_Msg.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"

#include "dds4ccm/impl/dds4ccm_conf.h"

namespace CIAO_CSL_QoSTest_Sender_Impl
{

  //============================================================
  // ConnectorStatusListener_exec_i
  //============================================================
  ConnectorStatusListener_exec_i::ConnectorStatusListener_exec_i (Atomic_Boolean &incompatible,
                                                                  Atomic_ThreadId &thread_id)
    : incompatible_ (incompatible),
      thread_id_ (thread_id)
  {
  }

  ConnectorStatusListener_exec_i::~ConnectorStatusListener_exec_i (void)
  {
  }

  // Operations from ::CCM_DDS::ConnectorStatusListener
  void ConnectorStatusListener_exec_i::on_inconsistent_topic(
    ::DDS::Topic_ptr /*the_topic*/,
    const DDS::InconsistentTopicStatus & /*status*/)
  {
  }

  void ConnectorStatusListener_exec_i::on_requested_incompatible_qos (
    ::DDS::DataReader_ptr /*the_reader*/,
    const DDS::RequestedIncompatibleQosStatus & /*status*/)
  {
  }

  void ConnectorStatusListener_exec_i::on_sample_rejected (
    ::DDS::DataReader_ptr /*the_reader*/,
    const DDS::SampleRejectedStatus & /*status*/)
  {
  }

  void ConnectorStatusListener_exec_i::on_offered_deadline_missed (
    ::DDS::DataWriter_ptr /*the_writer*/,
    const DDS::OfferedDeadlineMissedStatus & /*status*/)
  {
  }

  void ConnectorStatusListener_exec_i::on_offered_incompatible_qos (
    ::DDS::DataWriter_ptr the_writer,
    const DDS::OfferedIncompatibleQosStatus & /*status*/)
  {
    this->thread_id_ = ACE_Thread::self ();
    if(!CORBA::is_nil(the_writer))
      {
        this->incompatible_ = true;
      }
  }

  void ConnectorStatusListener_exec_i::on_unexpected_status (
    ::DDS::Entity_ptr /*the_entity*/,
    ::DDS::StatusKind  /*status_kind*/)
  {
  }
  //============================================================
  // Component Executor Implementation Class: Sender_exec_i
  //============================================================

  Sender_exec_i::Sender_exec_i (void)
    : incompatible_ (false),
      thread_id_listener_ (0)
  {
  }

  Sender_exec_i::~Sender_exec_i (void)
  {
  }

  ::CCM_DDS::CCM_ConnectorStatusListener_ptr
  Sender_exec_i::get_test_topic_connector_status (void)
  {
    return new ConnectorStatusListener_exec_i (this->incompatible_,
                                               this->thread_id_listener_);
  }

  // Supported operations and attributes.

  void
  Sender_exec_i::set_session_context (::Components::SessionContext_ptr ctx)
  {
    this->context_ =
      ::CSL_QoSTest::CCM_Sender_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
   }

  void
  Sender_exec_i::configuration_complete (void)
  {
  }

  void
  Sender_exec_i::ccm_activate (void)
  {
  }

  void
  Sender_exec_i::ccm_passivate (void)
  {
  }

  void
  Sender_exec_i::ccm_remove (void)
  {
    if (!this->incompatible_.value ())
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("SENDER ERROR: did not receive the expected ")
                               ACE_TEXT ("error 'on_requested_incompatible_Qos'\n")
                    ));
      }
    else
      {
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("SENDER OK: Received the expected ")
                               ACE_TEXT ("'on_requested_incompatible_Qos'\n")
                    ));
      }
    if (this->thread_id_listener_.value () == 0)
      {
        ACE_ERROR ((LM_ERROR, "SENDER ERROR: "
                              "Thread ID for ConnectorStatusListener not set!\n"));
      }
    #if (CIAO_DDS4CCM_CONTEXT_SWITCH == 1)
    else if (ACE_OS::thr_equal (this->thread_id_listener_.value (),
                                ACE_Thread::self ()))
      {
        ACE_DEBUG ((LM_DEBUG, "SENDER OK: "
                              "Thread switch for ConnectorStatusListener seems OK. "
                              "(DDS uses the CCM thread for its callback) "
                              "listener <%u> - component <%u>\n",
                              this->thread_id_listener_.value (),
                              ACE_Thread::self ()));
      }
    else
      {
        ACE_ERROR ((LM_ERROR, "SENDER ERROR: "
                              "Thread switch for ConnectorStatusListener "
                              "doesn't seem to work! "
                              "listener <%u> - component <%u>\n",
                              this->thread_id_listener_.value (),
                              ACE_Thread::self ()));
      }
    #else
    else if (ACE_OS::thr_equal (this->thread_id_listener_.value (),
                                ACE_Thread::self ()))
      {
        ACE_ERROR ((LM_ERROR, "SENDER ERROR: ConnectorStatusListener: "
                              "DDS seems to use a CCM thread for its callback: "
                              "listener <%u> - component <%u>\n",
                              this->thread_id_listener_.value (),
                              ACE_Thread::self ()));
      }
    else
      {
        ACE_DEBUG ((LM_DEBUG, "SENDER OK: ConnectorStatusListener: "
                              "DDS seems to use its own thread for its callback: "
                              "listener <%u> - component <%u>\n",
                              this->thread_id_listener_.value (),
                              ACE_Thread::self ()));
      }
    #endif
  }

  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_CSL_QoSTest_Sender_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Sender_exec_i);

    return retval;
  }
}
