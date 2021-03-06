/*  LabelModel.h
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

#ifndef LabelModel_h
#define LabelModel_h


#include "Settings.h"
#include "Template.h"

#include "Merge/Merge.h"
#include "Merge/Record.h"

#include <QList>
#include <QObject>
#include <QPainter>


namespace glabels
{

	// Forward References
	class ColorNode;
	class Handle;
	class LabelModelObject;
	class Region;

	///
	/// LabelModel
	///
	class LabelModel : public QObject
	{
		Q_OBJECT


		/////////////////////////////////
		// Lifecycle
		/////////////////////////////////
	public:
		LabelModel();
		~LabelModel() override {}

	
		/////////////////////////////////
		// Save/restore model state
		/////////////////////////////////
		LabelModel* save() const;
		void restore( const LabelModel *savedModel );
	

		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void changed();
		void nameChanged();
		void sizeChanged();
		void selectionChanged();
		void modifiedChanged();
		void mergeChanged();
		void mergeSourceChanged();
		void mergeSelectionChanged();


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		bool isModified() const;
		void setModified();
		void clearModified();

		QString shortName();
		const QString& fileName() const;
		void setFileName( const QString &fileName );

		int compressionLevel() const;
		void setCompressionLevel( int compressionLevel );

		const Template* tmplate() const;
		const Frame* frame() const;
		void setTmplate( const Template* tmplate );

		bool rotate() const;
		void setRotate( bool rotate );

		Distance w() const;
		Distance h() const;

		const QList<LabelModelObject*>& objectList() const;

		merge::Merge* merge() const;
		void setMerge( merge::Merge* merge );
	
		
		/////////////////////////////////
		// Manage objects
		/////////////////////////////////
	public:
		void addObject( LabelModelObject* object );
		void deleteObject( LabelModelObject* object );

		LabelModelObject* objectAt( double          scale,
		                            const Distance& x,
		                            const Distance& y ) const;
		
		Handle* handleAt( double          scale,
		                  const Distance& x,
		                  const Distance& y ) const;


		/////////////////////////////////
		// Manipulate selection
		/////////////////////////////////
	public:
		void selectObject( LabelModelObject* object );
		void unselectObject( LabelModelObject* object );
		void selectAll();
		void unselectAll();
		void selectRegion( const Region& region );
		bool isSelectionEmpty();
		bool isSelectionAtomic();


		/////////////////////////////////
		// Get selected objects
		/////////////////////////////////
	public:
		QList<LabelModelObject*> getSelection();
		LabelModelObject* getFirstSelectedObject();


		/////////////////////////////////
		// Query selection capabilities
		/////////////////////////////////
	public:
		bool canSelectionText();
		bool canSelectionFill();
		bool canSelectionLineColor();
		bool canSelectionLineWidth();


		/////////////////////////////////
		// Operations on selections
		/////////////////////////////////
	public:
		void deleteSelection();
		void raiseSelectionToTop();
		void lowerSelectionToBottom();
		void rotateSelection( double thetaDegs );
		void rotateSelectionLeft();
		void rotateSelectionRight();
		void flipSelectionHoriz();
		void flipSelectionVert();
		void alignSelectionLeft();
		void alignSelectionRight();
		void alignSelectionHCenter();
		void alignSelectionTop();
		void alignSelectionBottom();
		void alignSelectionVCenter();
		void centerSelectionHoriz();
		void centerSelectionVert();
		void moveSelection( const Distance& dx, const Distance& dy );
		void setSelectionFontFamily( const QString& fontFamily );
		void setSelectionFontSize( double fontSize );
		void setSelectionFontWeight( QFont::Weight fontWeight );
		void setSelectionFontItalicFlag( bool fontItalicFlag );
		void setSelectionTextHAlign( Qt::Alignment textHAlign );
		void setSelectionTextVAlign( Qt::Alignment textVAlign );
		void setSelectionTextLineSpacing( double textLineSpacing );
		void setSelectionTextColorNode( ColorNode textColorNode );
		void setSelectionLineWidth( const Distance& lineWidth );
		void setSelectionLineColorNode( ColorNode lineColorNode );
		void setSelectionFillColorNode( ColorNode fillColorNode );


		/////////////////////////////////
		// Clipboard operations
		/////////////////////////////////
		void copySelection();
		void cutSelection();
		bool canPaste();
		void paste();
	
		/////////////////////////////////
		// Drawing operations
		/////////////////////////////////
	public:
		void draw( QPainter* painter, bool inEditor = true, merge::Record* record = nullptr ) const;

		
		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onObjectChanged();
		void onObjectMoved();
		void onMergeSourceChanged();
		void onMergeSelectionChanged();


		/////////////////////////////////
		// Private data
		/////////////////////////////////
	private:
		int                       mUntitledInstance;
		bool                      mModified;
		QString                   mFileName;
		int                       mCompressionLevel;
		const Template*           mTmplate;
		const Frame*              mFrame;
		bool                      mRotate;

		QList<LabelModelObject*>  mObjectList;

		merge::Merge*             mMerge;
	};

}


#endif // LabelModel_h
