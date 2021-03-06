/*  LabelModelBoxObject.cpp
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

#include "LabelModelBoxObject.h"

#include <QBrush>
#include <QPen>


namespace glabels
{

	//
	// Private
	//
	namespace
	{
		const double slopPixels = 2;
	}


	///
	/// Constructor
	///
	LabelModelBoxObject::LabelModelBoxObject()
	{
		// empty
	}


	///
	/// Constructor
	///
	LabelModelBoxObject::LabelModelBoxObject( const Distance&  x0,
	                                          const Distance&  y0,
	                                          const Distance&  w,
	                                          const Distance&  h,
	                                          const Distance&  lineWidth,
	                                          const ColorNode& lineColorNode,
	                                          const ColorNode& fillColorNode,
	                                          const QMatrix&   matrix,
	                                          bool             shadowState,
	                                          const Distance&  shadowX,
	                                          const Distance&  shadowY,
	                                          double           shadowOpacity,
	                                          const ColorNode& shadowColorNode )
	: LabelModelShapeObject( x0, y0, w, h,
	                         lineWidth, lineColorNode, fillColorNode,
	                         matrix,
	                         shadowState, shadowX, shadowY, shadowOpacity, shadowColorNode )
	{
		// empty
	}


	///
	/// Copy constructor
	///
	LabelModelBoxObject::LabelModelBoxObject( const LabelModelBoxObject* object )
		: LabelModelShapeObject( object )
	{
		// empty
	}


	///
	/// Destructor
	///
	LabelModelBoxObject::~LabelModelBoxObject()
	{
		// empty
	}


	///
	/// Clone
	///
	LabelModelBoxObject* LabelModelBoxObject::clone() const
	{
		return new LabelModelBoxObject( this );
	}


	///
	/// Draw shadow of object
	///
	void LabelModelBoxObject::drawShadow( QPainter* painter, bool inEditor, merge::Record* record ) const
	{
		QColor lineColor = mLineColorNode.color( record );
		QColor fillColor = mFillColorNode.color( record );
		QColor shadowColor = mShadowColorNode.color( record );

		shadowColor.setAlphaF( mShadowOpacity );

		if ( fillColor.alpha() )
		{
			painter->setPen( Qt::NoPen );
			painter->setBrush( shadowColor );

			if ( lineColor.alpha() )
			{
				/* Has FILL and OUTLINE: adjust size to account for line width. */
				painter->drawRect( QRectF( -mLineWidth.pt()/2,
				                           -mLineWidth.pt()/2,
				                           (mW + mLineWidth).pt(),
				                           (mH + mLineWidth).pt() ) );
			}
			else
			{
				/* Has FILL, but no OUTLINE. */
				painter->drawRect( QRectF( 0, 0, mW.pt(), mH.pt() ) );
			}
		}
		else
		{
			if ( lineColor.alpha() )
			{
				/* Has only OUTLINE. */
				painter->setPen( QPen( shadowColor, mLineWidth.pt() ) );
				painter->setBrush( Qt::NoBrush );

				painter->drawRect( QRectF( 0, 0, mW.pt(), mH.pt() ) );
			}
		}
		
	}

	
	///
	/// Draw object itself
	///
	void LabelModelBoxObject::drawObject( QPainter* painter, bool inEditor, merge::Record* record ) const
	{
		QColor lineColor = mLineColorNode.color( record );
		QColor fillColor = mFillColorNode.color( record );

		painter->setPen( QPen( lineColor, mLineWidth.pt() ) );
		painter->setBrush( fillColor );

		painter->drawRect( QRectF( 0, 0, mW.pt(), mH.pt() ) );
	}


	///
	/// Path to test for hover condition
	///
	QPainterPath LabelModelBoxObject::hoverPath( double scale ) const
	{
		double s = 1 / scale;

		QPainterPath path;

		if ( mFillColorNode.color().alpha() && mLineColorNode.color().alpha() )
		{
			path.addRect( -mLineWidth.pt()/2, -mLineWidth.pt()/2, (mW+mLineWidth).pt(), (mH+mLineWidth).pt() );
		}
		else if ( mFillColorNode.color().alpha() && !(mLineColorNode.color().alpha()) )
		{
			path.addRect( 0, 0, mW.pt(), mH.pt() );
		}
		else if ( mLineColorNode.color().alpha() )
		{
			path.addRect( (-mLineWidth.pt()/2) - s*slopPixels,
			              (-mLineWidth.pt()/2) - s*slopPixels,
			              (mW + mLineWidth).pt() + s*2*slopPixels,
			              (mH + mLineWidth).pt() + s*2*slopPixels );
			path.closeSubpath();
			path.addRect( mLineWidth.pt()/2 + s*slopPixels,
			              mLineWidth.pt()/2 + s*slopPixels,
			              (mW - mLineWidth).pt() - s*2*slopPixels,
			              (mH - mLineWidth).pt() - s*2*slopPixels );
		}

		return path;
	}

} // namespace glabels
