// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef __Example__GeometryExtension__
#define __Example__GeometryExtension__

#include <iostream>
#include <metaioSDK/IMetaioSDK.h>

namespace metaio
{

class METAIO_DLL_API GeometryExtension
{
    // a pointer to the geometry
    metaio::IGeometry* m_geometry;
    
    // if a geometry is selected
    bool m_selected;
    
    // which group the geometry belongs to
    int m_group;
    
    // initial rotation
    metaio::Rotation m_referenceRotation;
    
    // initial scale
    metaio::Vector3d m_referenceScale;
    
    // original scale of geometry from the loading the state
    metaio::Vector3d m_originalScale;
    
    // the coordinate of the difference between the touch point and the pivot point in the geometry
	metaio::Vector3d m_referenceOffset;
    
public:
    
    /**
     * \brief Constructor for the class GeometryExtension.
     * \param geometry A pointer to the geometry.
     * \param group Specity the group number of the geometry.
     */
    GeometryExtension(metaio::IGeometry* geometry, int group);
    
    
    /**
     * \brief Destructor for the class GeometryExtension.
     */
    ~GeometryExtension();
    
    
    /**
     * \brief Get the pointer to the geometry.
     * \return m_geometry The pointer to the geoemtry.
     */
    metaio::IGeometry* getGeometry();
    
    
    /**
     * \brief Test if the geometry is touched.
     * \param geometry A pointer to a geometry
     * \param metaioSDK A pointer to the metaioSDK.
	 * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     * \return True if the geometry is touched, false otherwise.
     */
    bool select(metaio::IGeometry* geometry, metaio::IMetaioSDK* metaioSDK, int x, int y);
    
    
    /**
     * \brief Record the initial states of the geometries.
     * \param metaioSDK A pointer to the metaioSDK.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void setSelected(metaio::IMetaioSDK* metaioSDK, int x, int y);
    
    
    /**
     * \brief Deselect the geometry.
     */
    void reset();
    
    
    /**
     * \brief Get the selected state of the geometry.
     * \return True if the goemtry is selected, false othewise.
     */
    bool isSelected();
    
    
    /**
     * \brief Get the group number of the geometry.
     * \return m_group The group that the geometry belongs to.
     */
    int getGroup();
    
    
    /**
     * \brief Move the geoemtry if selected.
     * \param metaioSDK A pointer to the metaioSDK.
     * \param x The x coordinate of the touch point.
     * \param y The y coordinate of the touch point.
     */
    void setTranslationFromScreen(metaio::IMetaioSDK* metaioSDK, int x, int y);
    
    
    /**
     * \brief Rotate the geometry if selected.
     * \param rotation The rotation in radians that should be applied to the geometry.
     * \param axis The axis that the rotation should be applied to.
     */
    void setRotation(float rotation, char axis);
    
    
    /**
     * \brief Scale the geometry if selected.
     * \param scale The scale that should be applied to the geometry.
     */
    void setScale(float scale);
};

} // namespace metaio

#endif /* defined(__Example__GeometryExtension__) */
