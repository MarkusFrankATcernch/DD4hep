//==========================================================================
//  AIDA Detector description implementation 
//--------------------------------------------------------------------------
// Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
// All rights reserved.
//
// For the licensing terms see $DD4hepINSTALL/LICENSE.
// For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
//
// Author     : M.Frank
//
//==========================================================================
#ifndef DD4HEP_GEOHANDLER_H
#define DD4HEP_GEOHANDLER_H

/// Framework include files
#include <DD4hep/Detector.h>

/// C/C++ include files
#include <set>
#include <map>
#include <vector>

// Forward declarations
class TGeoMatrix;
class TGeoVolume;
class TGeoMedium;
class TGeoShape;
class TGeoNode;

/// Namespace for the AIDA detector description toolkit
namespace dd4hep {

  // Forward declarations
  class  Detector;
  class  NamedObject;
  class  DetElement;
  class  SensitiveDetector;
  class  VisAttrObject;
  class  Volume;
  class  PlacedVolume;

  /// Namespace for implementation details of the AIDA detector description toolkit
  namespace detail {

    /// Defintion of the object types used by generic geometry handlers
    /**
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_CORE
     */
    class GeoHandlerTypes {
    public:
      /// Data container to store information obtained during the geometry scan
      /**
       *  \author  M.Frank
       *  \version 1.0
       *  \ingroup DD4HEP_CORE
       */
      class GeometryInfo {
      public:
        std::vector<TGeoShape*>   solids;
        std::set<TGeoShape*>   solid_set;
        std::set<Volume>       volumeSet;
        std::vector<Volume>    volumes;
        std::set<VisAttr>      vis;
        std::set<Ref_t>        fields;
        std::set<Material>     materials;
        std::set<TGeoMedium*>  media;
        std::set<TGeoElement*> elements;
        std::vector<std::pair<std::string, TGeoMatrix*> > trafos;
      };
    };

    /// The base class for all dd4hep geometry crawlers
    /**
     *  Geometry crawlers are used for multiple purposes, whenever entire
     *  geometries must be traversed like e.g. to create a new geometry
     *  for simulation etc.
     *  While analysing the geometry, information is collected, which
     *  may be later processed.
     *
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_CORE
     */
    class GeoHandler: public GeoHandlerTypes {

    protected:
      bool  m_propagateRegions { false };
      std::map<int, std::vector<const TGeoNode*> >*    m_data      { nullptr };
      std::map<const TGeoNode*, std::vector<TGeoNode*> >* m_daughters { nullptr };
      /// Internal helper to collect geometry information from traversal
      GeoHandler& i_collect(const TGeoNode* parent,
                            const TGeoNode* node,
                            int level, Region rg, LimitSet ls);

    private:
      /// Never call Copy constructor
      GeoHandler(const GeoHandler&) {
      }
      /// Never call assignment operator
      GeoHandler& operator=(const GeoHandler&) {
        return *this;
      }

    public:
      /// Default constructor
      GeoHandler();
      /// Initializing constructor
      GeoHandler(std::map<int, std::vector<const TGeoNode*> >* ptr,
                 std::map<const TGeoNode*, std::vector<TGeoNode*> >* daus = nullptr);
      /// Default destructor
      virtual ~GeoHandler();
      /// Propagate regions. Returns the previous value
      bool setPropagateRegions(bool value);
      /// Collect geometry information from traversal
      GeoHandler& collect(DetElement top);
      /// Collect geometry information from traversal with aggregated information
      GeoHandler& collect(DetElement top, GeometryInfo& info);
      /// Access to collected node list
      std::map<int, std::vector<const TGeoNode*> >* release();
    };

    /// Geometry scanner (handle object)
    /**
     *  \author  M.Frank
     *  \version 1.0
     *  \ingroup DD4HEP_CORE
     */
    class GeoScan {
    protected:
      /// Data holder
      std::map<int, std::vector<const TGeoNode*> >* m_data;
    public:
      /// Initializing constructor
      GeoScan(DetElement e);
      /// Initializing constructor
      GeoScan(DetElement e, bool propagateRegions);
      /// Default destructor
      virtual ~GeoScan();
      /// Work callback
      virtual GeoScan& operator()();
    };
  }    // End namespace detail
}      // End namespace dd4hep

#endif // DD4HEP_GEOHANDLER_H
