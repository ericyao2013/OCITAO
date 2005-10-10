/* $Id$
 * This code was generated by the XML Schema Compiler.
 *
 * Changes made to this code will most likely be overwritten
 * when the handlers are recompiled.
 * 
 * If you find errors or feel that there are bugfixes to be made,
 * please contact the current XSC maintainer:
 *             Will Otte <wotte@dre.vanderbilt.edu>
 */


// Fixes the VC6 warning 4786.
#include "vc6-4786.h"
 
// Fix for Borland compilers, which seem to have a broken
// <string> include.
#ifdef __BORLANDC__
# include <string.h>
#endif

#include "XSC_XML_Handlers_Export.h"
#ifndef CDP_HPP
#define CDP_HPP

// Forward declarations.
//
namespace CIAO
{
  namespace Config_Handlers
  {
    class DeploymentPlan;
  }
}

#include <memory>
#include <vector>
#include "XMLSchema/Types.hpp"

#include "ccd.hpp"

namespace CIAO
{
  namespace Config_Handlers
  {
    class XSC_XML_Handlers_Export DeploymentPlan : public ::XSCRT::Type
    {
      //@@ VC6 anathema
      typedef ::XSCRT::Type Base__;

      // label
      // 
      public:
      bool label_p () const;
      ::XMLSchema::string< ACE_TCHAR > const& label () const;
      void label (::XMLSchema::string< ACE_TCHAR > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > label_;

      // UUID
      // 
      public:
      bool UUID_p () const;
      ::XMLSchema::string< ACE_TCHAR > const& UUID () const;
      void UUID (::XMLSchema::string< ACE_TCHAR > const& );

      protected:
      ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > UUID_;

      // realizes
      // 
      public:
      bool realizes_p () const;
      ::CIAO::Config_Handlers::ComponentInterfaceDescription const& realizes () const;
      void realizes (::CIAO::Config_Handlers::ComponentInterfaceDescription const& );

      protected:
      ::std::auto_ptr< ::CIAO::Config_Handlers::ComponentInterfaceDescription > realizes_;

      // implementation
      // 
      public:
      typedef ::std::vector< ::CIAO::Config_Handlers::MonolithicDeploymentDescription >::iterator implementation_iterator;
      typedef ::std::vector< ::CIAO::Config_Handlers::MonolithicDeploymentDescription >::const_iterator implementation_const_iterator;
      implementation_iterator begin_implementation ();
      implementation_iterator end_implementation ();
      implementation_const_iterator begin_implementation () const;
      implementation_const_iterator end_implementation () const;
      void add_implementation (::CIAO::Config_Handlers::MonolithicDeploymentDescription const& );
      size_t count_implementation (void) const;

      protected:
      ::std::vector< ::CIAO::Config_Handlers::MonolithicDeploymentDescription > implementation_;

      // instance
      // 
      public:
      typedef ::std::vector< ::CIAO::Config_Handlers::InstanceDeploymentDescription >::iterator instance_iterator;
      typedef ::std::vector< ::CIAO::Config_Handlers::InstanceDeploymentDescription >::const_iterator instance_const_iterator;
      instance_iterator begin_instance ();
      instance_iterator end_instance ();
      instance_const_iterator begin_instance () const;
      instance_const_iterator end_instance () const;
      void add_instance (::CIAO::Config_Handlers::InstanceDeploymentDescription const& );
      size_t count_instance (void) const;

      protected:
      ::std::vector< ::CIAO::Config_Handlers::InstanceDeploymentDescription > instance_;

      // connection
      // 
      public:
      typedef ::std::vector< ::CIAO::Config_Handlers::PlanConnectionDescription >::iterator connection_iterator;
      typedef ::std::vector< ::CIAO::Config_Handlers::PlanConnectionDescription >::const_iterator connection_const_iterator;
      connection_iterator begin_connection ();
      connection_iterator end_connection ();
      connection_const_iterator begin_connection () const;
      connection_const_iterator end_connection () const;
      void add_connection (::CIAO::Config_Handlers::PlanConnectionDescription const& );
      size_t count_connection (void) const;

      protected:
      ::std::vector< ::CIAO::Config_Handlers::PlanConnectionDescription > connection_;

      // dependsOn
      // 
      public:
      typedef ::std::vector< ::CIAO::Config_Handlers::ImplementationDependency >::iterator dependsOn_iterator;
      typedef ::std::vector< ::CIAO::Config_Handlers::ImplementationDependency >::const_iterator dependsOn_const_iterator;
      dependsOn_iterator begin_dependsOn ();
      dependsOn_iterator end_dependsOn ();
      dependsOn_const_iterator begin_dependsOn () const;
      dependsOn_const_iterator end_dependsOn () const;
      void add_dependsOn (::CIAO::Config_Handlers::ImplementationDependency const& );
      size_t count_dependsOn (void) const;

      protected:
      ::std::vector< ::CIAO::Config_Handlers::ImplementationDependency > dependsOn_;

      // artifact
      // 
      public:
      typedef ::std::vector< ::CIAO::Config_Handlers::ArtifactDeploymentDescription >::iterator artifact_iterator;
      typedef ::std::vector< ::CIAO::Config_Handlers::ArtifactDeploymentDescription >::const_iterator artifact_const_iterator;
      artifact_iterator begin_artifact ();
      artifact_iterator end_artifact ();
      artifact_const_iterator begin_artifact () const;
      artifact_const_iterator end_artifact () const;
      void add_artifact (::CIAO::Config_Handlers::ArtifactDeploymentDescription const& );
      size_t count_artifact (void) const;

      protected:
      ::std::vector< ::CIAO::Config_Handlers::ArtifactDeploymentDescription > artifact_;

      // infoProperty
      // 
      public:
      typedef ::std::vector< ::CIAO::Config_Handlers::Property >::iterator infoProperty_iterator;
      typedef ::std::vector< ::CIAO::Config_Handlers::Property >::const_iterator infoProperty_const_iterator;
      infoProperty_iterator begin_infoProperty ();
      infoProperty_iterator end_infoProperty ();
      infoProperty_const_iterator begin_infoProperty () const;
      infoProperty_const_iterator end_infoProperty () const;
      void add_infoProperty (::CIAO::Config_Handlers::Property const& );
      size_t count_infoProperty (void) const;

      protected:
      ::std::vector< ::CIAO::Config_Handlers::Property > infoProperty_;

      public:
      DeploymentPlan ();

      DeploymentPlan (::XSCRT::XML::Element< ACE_TCHAR > const&);
      DeploymentPlan (DeploymentPlan const& s);

      DeploymentPlan&
      operator= (DeploymentPlan const& s);

      private:
      char regulator__;
    };
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
  }
}

#include "XMLSchema/Traversal.hpp"

namespace CIAO
{
  namespace Config_Handlers
  {
    namespace Traversal
    {
      struct XSC_XML_Handlers_Export DeploymentPlan : ::XMLSchema::Traversal::Traverser< ::CIAO::Config_Handlers::DeploymentPlan >
      {
        virtual void
        traverse (Type&);

        virtual void
        traverse (Type const&);

        virtual void
        pre (Type&);

        virtual void
        pre (Type const&);

        virtual void
        label (Type&);

        virtual void
        label (Type const&);

        virtual void
        label_none (Type&);

        virtual void
        label_none (Type const&);

        virtual void
        UUID (Type&);

        virtual void
        UUID (Type const&);

        virtual void
        UUID_none (Type&);

        virtual void
        UUID_none (Type const&);

        virtual void
        realizes (Type&);

        virtual void
        realizes (Type const&);

        virtual void
        realizes_none (Type&);

        virtual void
        realizes_none (Type const&);

        virtual void
        implementation (Type&);

        virtual void
        implementation (Type const&);

        virtual void
        implementation_pre (Type&);

        virtual void
        implementation_pre (Type const&);

        virtual void
        implementation_next (Type&);

        virtual void
        implementation_next (Type const&);

        virtual void
        implementation_post (Type&);

        virtual void
        implementation_post (Type const&);

        virtual void
        instance (Type&);

        virtual void
        instance (Type const&);

        virtual void
        instance_pre (Type&);

        virtual void
        instance_pre (Type const&);

        virtual void
        instance_next (Type&);

        virtual void
        instance_next (Type const&);

        virtual void
        instance_post (Type&);

        virtual void
        instance_post (Type const&);

        virtual void
        instance_none (Type&);

        virtual void
        instance_none (Type const&);

        virtual void
        connection (Type&);

        virtual void
        connection (Type const&);

        virtual void
        connection_pre (Type&);

        virtual void
        connection_pre (Type const&);

        virtual void
        connection_next (Type&);

        virtual void
        connection_next (Type const&);

        virtual void
        connection_post (Type&);

        virtual void
        connection_post (Type const&);

        virtual void
        connection_none (Type&);

        virtual void
        connection_none (Type const&);

        virtual void
        dependsOn (Type&);

        virtual void
        dependsOn (Type const&);

        virtual void
        dependsOn_pre (Type&);

        virtual void
        dependsOn_pre (Type const&);

        virtual void
        dependsOn_next (Type&);

        virtual void
        dependsOn_next (Type const&);

        virtual void
        dependsOn_post (Type&);

        virtual void
        dependsOn_post (Type const&);

        virtual void
        dependsOn_none (Type&);

        virtual void
        dependsOn_none (Type const&);

        virtual void
        artifact (Type&);

        virtual void
        artifact (Type const&);

        virtual void
        artifact_pre (Type&);

        virtual void
        artifact_pre (Type const&);

        virtual void
        artifact_next (Type&);

        virtual void
        artifact_next (Type const&);

        virtual void
        artifact_post (Type&);

        virtual void
        artifact_post (Type const&);

        virtual void
        artifact_none (Type&);

        virtual void
        artifact_none (Type const&);

        virtual void
        infoProperty (Type&);

        virtual void
        infoProperty (Type const&);

        virtual void
        infoProperty_pre (Type&);

        virtual void
        infoProperty_pre (Type const&);

        virtual void
        infoProperty_next (Type&);

        virtual void
        infoProperty_next (Type const&);

        virtual void
        infoProperty_post (Type&);

        virtual void
        infoProperty_post (Type const&);

        virtual void
        infoProperty_none (Type&);

        virtual void
        infoProperty_none (Type const&);

        virtual void
        post (Type&);

        virtual void
        post (Type const&);
      };
    }
  }
}

#include "XMLSchema/Writer.hpp"

namespace CIAO
{
  namespace Config_Handlers
  {
    namespace Writer
    {
      struct XSC_XML_Handlers_Export DeploymentPlan : Traversal::DeploymentPlan, 
      virtual ::XSCRT::Writer< ACE_TCHAR >
      {
        typedef ::CIAO::Config_Handlers::DeploymentPlan Type;
        DeploymentPlan (::XSCRT::XML::Element< ACE_TCHAR >&);

        #ifdef __BORLANDC__
        virtual void 
        traverse (Type &o)
        {

          this->traverse (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        traverse (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        label (Type &o)
        {

          this->label (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        label (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        UUID (Type &o)
        {

          this->UUID (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        UUID (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        realizes (Type &o)
        {

          this->realizes (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        realizes (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        implementation_pre (Type &o)
        {

          this->implementation_pre (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        implementation_pre (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        implementation_next (Type &o)
        {

          this->implementation_next (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        implementation_next (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        implementation_post (Type &o)
        {

          this->implementation_post (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        implementation_post (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        instance_pre (Type &o)
        {

          this->instance_pre (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        instance_pre (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        instance_next (Type &o)
        {

          this->instance_next (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        instance_next (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        instance_post (Type &o)
        {

          this->instance_post (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        instance_post (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        connection_pre (Type &o)
        {

          this->connection_pre (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        connection_pre (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        connection_next (Type &o)
        {

          this->connection_next (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        connection_next (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        connection_post (Type &o)
        {

          this->connection_post (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        connection_post (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        dependsOn_pre (Type &o)
        {

          this->dependsOn_pre (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        dependsOn_pre (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        dependsOn_next (Type &o)
        {

          this->dependsOn_next (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        dependsOn_next (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        dependsOn_post (Type &o)
        {

          this->dependsOn_post (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        dependsOn_post (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        artifact_pre (Type &o)
        {

          this->artifact_pre (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        artifact_pre (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        artifact_next (Type &o)
        {

          this->artifact_next (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        artifact_next (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        artifact_post (Type &o)
        {

          this->artifact_post (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        artifact_post (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        infoProperty_pre (Type &o)
        {

          this->infoProperty_pre (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        infoProperty_pre (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        infoProperty_next (Type &o)
        {

          this->infoProperty_next (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        infoProperty_next (Type const&);

        // Hack to make borland stop complaining.  
        #ifdef __BORLANDC__
        virtual void 
        infoProperty_post (Type &o)
        {

          this->infoProperty_post (const_cast <Type const &> (o));
        }


        #endif /* __BORLANDC__ */
        virtual void
        infoProperty_post (Type const&);

        protected:
        DeploymentPlan ();
      };
    }
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
  }
}

#endif // CDP_HPP
