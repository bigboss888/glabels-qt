/*  LabelModelLineObject.h
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LabelModelLineObject_h
#define LabelModelLineObject_h


#include "LabelModelObject.h"


namespace glabels
{

	///
	/// Label Model Line Object
	///
	class LabelModelLineObject : public LabelModelObject
	{
		Q_OBJECT

		///////////////////////////////////////////////////////////////
		// Lifecycle Methods
		///////////////////////////////////////////////////////////////
	public:
		LabelModelLineObject();

		LabelModelLineObject( const Distance&  x0,
		                      const Distance&  y0,
		                      const Distance&  w,
		                      const Distance&  h,
		                      const Distance&  lineWidth,
		                      const ColorNode& lineColorNode,
		                      const QMatrix&   matrix = QMatrix(),
		                      bool             shadowState = false,
		                      const Distance&  shadowX = 0,
		                      const Distance&  shadowY = 0,
		                      double           shadowOpacity = 1.0,
		                      const ColorNode& shadowColorNode = ColorNode() );

		LabelModelLineObject( const LabelModelLineObject* object );
		
		~LabelModelLineObject() override;


		///////////////////////////////////////////////////////////////
		// Object duplication
		///////////////////////////////////////////////////////////////
		LabelModelLineObject* clone() const override;


		///////////////////////////////////////////////////////////////
		// Property Implementations
		///////////////////////////////////////////////////////////////
	public:
		//
		// Line Property: lineWidth
		//
		Distance lineWidth() const override;
		void setLineWidth( const Distance& value ) override;


		//
		// Line Property: lineColorNode
		//
		ColorNode lineColorNode() const override;
		void setLineColorNode( const ColorNode& value ) override;
		

		///////////////////////////////////////////////////////////////
		// Capability Implementations
		///////////////////////////////////////////////////////////////
	public:
		virtual bool canLineColor();
		virtual bool canLineWidth();


		///////////////////////////////////////////////////////////////
		// Drawing operations
		///////////////////////////////////////////////////////////////
	protected:
		void drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		void drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const override;
		QPainterPath hoverPath( double scale ) const override;


		///////////////////////////////////////////////////////////////
		// Private Members
		///////////////////////////////////////////////////////////////
	protected:
		Distance    mLineWidth;
		ColorNode   mLineColorNode;

	};

}


#endif // LabelModelLineObject_h
