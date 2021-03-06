/*  RawText.h
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#ifndef RawText_h
#define RawText_h


#include "Merge/Record.h"

#include <QString>


namespace glabels
{

	///
	/// Raw Text Type
	///
	struct RawText
	{

		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		RawText() = default;
		RawText( const QString& string );
		RawText( const char* cString );


		/////////////////////////////////
		// Misc. Methods
		/////////////////////////////////
		QString toString() const;
		std::string toStdString() const;
		QString expand( merge::Record* record ) const;
		bool hasPlaceHolders() const;
		bool isEmpty() const;

		
		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		QString mString;

	};

}


#endif // RawText_h
