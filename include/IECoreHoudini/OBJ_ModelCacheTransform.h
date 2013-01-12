//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2013, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of Image Engine Design nor the names of any
//       other contributors to this software may be used to endorse or
//       promote products derived from this software without specific prior
//       written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#ifndef IECOREHOUDINI_OBJMODELCACHETRANSFORM_H
#define IECOREHOUDINI_OBJMODELCACHETRANSFORM_H

#include "OBJ/OBJ_SubNet.h"

#include "IECoreHoudini/OBJ_ModelCacheNode.h"

namespace IECoreHoudini
{

/// OBJ for loading a transform or building a hierarchy from an IECore::ModelCache
class OBJ_ModelCacheTransform : public OBJ_ModelCacheNode<OBJ_SubNet>
{
	public :
		
		OBJ_ModelCacheTransform( OP_Network *net, const char *name, OP_Operator *op );
		virtual ~OBJ_ModelCacheTransform();
		
		static const char *typeName;
		
		static OP_Node *create( OP_Network *net, const char *name, OP_Operator *op );
		static OP_TemplatePair *buildParameters();
		
		static PRM_Name pHierarchy;
		static PRM_Name pDepth;
		
		static PRM_Default hierarchyDefault;
		static PRM_Default depthDefault;
		
		static PRM_ChoiceList hierarchyList;
		static PRM_ChoiceList depthList;
		
		enum Hierarchy
		{
			SubNetworks,
			Parenting,
			FlatGeometry
		};
		
		enum Depth
		{
			AllDescendants,
			Children
		};
		
		/// Implemented to build the ModelCache using a combination of OBJ_ModelCacheTransform
		/// and/or OBJ_ModelCacheGeometry nodes depending on the settings for pHierarchy and pDepth.
		/// Derived classes should re-implement doBuildObject() and doBuildChild() if specialized
		/// behaviour is necessary.
		virtual void buildHierarchy( const IECore::ModelCache *cache );
	
	protected :
		
		/// Called by buildHierarchy() when the ModelCache contains an object.
		/// Implemented to build the specific object using an OBJ_ModelCacheGeometry node.
		virtual OBJ_Node *doBuildObject( const IECore::ModelCache *cache, OP_Network *parent, Hierarchy hierarchy, Depth depth );
		
		/// Called by buildHierarchy() for each child of the ModelCache it was given.
		/// Implemented to build the current cache path using an OBJ_ModelCacheTransform or
		/// OBJ_ModelCacheGeometry node depending on the settings for hierarchy and depth.
		virtual OBJ_Node *doBuildChild( const IECore::ModelCache *cache, OP_Network *parent, Hierarchy hierarchy, Depth depth );
		
		virtual void doBuildChildren( const IECore::ModelCache *cache, OP_Network *parent, Hierarchy hierarchy, Depth depth );

};

} // namespace IECoreHoudini

#endif // IECOREHOUDINI_OBJMODELCACHETRANSFORM_H