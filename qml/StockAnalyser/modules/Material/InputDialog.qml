/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2015 Michael Spencer <sonrisesoftware@gmail.com>
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
import Material 0.2

/*!
   \qmltype InputDialog
   \inqmlmodule Material

   \brief A dialog with a single text field input.
 */
Dialog {
    id: inputDialog
    
    hasActions: true

    positiveButtonEnabled: textField.acceptableInput

    property alias textField: textField

    property alias validator: textField.validator
    property alias inputMask: textField.inputMask
    property alias inputMethodHints: textField.inputMethodHints
    
    property alias placeholderText: textField.placeholderText
    property alias value: textField.text

    TextField {
        id: textField

        anchors {
            left: parent.left
            right: parent.right
        }
    }
}
