/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2014 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.4

/*!
   \qmltype ThinDivider
   \inqmlmodule Material

   \brief A 1dp high divider for use in lists and other columns of content.
 */
Rectangle {
    anchors {
        left: parent.left
        right: parent.right
    }

    color: Qt.rgba(0,0,0,0.1)
    height: 1
}
