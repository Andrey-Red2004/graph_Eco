import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Rectangle {
    id: root
    color: "#eef2f9"
    radius: 14

    Material.theme: Material.Light
    Material.accent: "#4f7cff"

    property var pisos: ["Universidad", "Piso 1", "Piso 2", "Piso 3", "Piso 4", "Piso 5"]

    ScrollView {
        anchors.fill: parent
        padding: 16
        clip: true

        ColumnLayout {
            width: parent.width - 8
            spacing: 14

            Rectangle {
                Layout.fillWidth: true
                color: "#ffffff"
                radius: 12
                border.color: "#d9e0ee"
                implicitHeight: 64

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 10

                    Rectangle {
                        width: 10
                        height: 36
                        radius: 6
                        color: "#4f7cff"
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "EcoCampus"
                            font.pixelSize: 18
                            font.bold: true
                            color: "#1f2a44"
                        }
                        Text {
                            text: "Control de recorridos"
                            font.pixelSize: 12
                            color: "#6c7a96"
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                color: "#ffffff"
                radius: 12
                border.color: "#d9e0ee"
                Layout.preferredHeight: 160

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    Text {
                        text: "Mapa"
                        font.pixelSize: 13
                        color: "#6c7a96"
                    }

                    ComboBox {
                        id: pisoCombo
                        model: pisos
                        Layout.fillWidth: true
                        currentIndex: pisos.indexOf(bridge.pisoActual)
                        onCurrentTextChanged: bridge.pisoActual = currentText
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Layout.topMargin: 4

                        CheckBox {
                            text: "Biblioteca"
                            checked: bridge.mostrarBiblioteca
                            onToggled: bridge.mostrarBiblioteca = checked
                        }

                        CheckBox {
                            text: "Comedor"
                            checked: bridge.mostrarComedor
                            onToggled: bridge.mostrarComedor = checked
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                color: "#ffffff"
                radius: 12
                border.color: "#d9e0ee"
                Layout.preferredHeight: 160

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    Text {
                        text: "Inicio"
                        font.pixelSize: 13
                        color: "#6c7a96"
                    }

                    SpinBox {
                        id: inicioBox
                        from: 1
                        value: bridge.inicio
                        editable: true
                        Layout.fillWidth: true
                        implicitHeight: 42
                        onValueChanged: {
                            if (bridge.inicio !== value)
                                bridge.inicio = value
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Layout.topMargin: 6

                        Button {
                            text: "DFS"
                            Layout.fillWidth: true
                            implicitHeight: 36
                            onClicked: bridge.requestDfs()
                        }

                        Button {
                            text: "BFS"
                            Layout.fillWidth: true
                            implicitHeight: 36
                            onClicked: bridge.requestBfs()
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                color: "#ffffff"
                radius: 12
                border.color: "#d9e0ee"
                Layout.preferredHeight: 110

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 6

                    Text {
                        text: "Resultados"
                        font.pixelSize: 13
                        color: "#6c7a96"
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Tiempo"
                            color: "#1f2a44"
                            font.pixelSize: 13
                        }
                        Item { Layout.fillWidth: true }
                        Text {
                            text: bridge.tiempo
                            color: "#4f7cff"
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Visitados"
                            color: "#1f2a44"
                            font.pixelSize: 13
                        }
                        Item { Layout.fillWidth: true }
                        Text {
                            text: bridge.visitados
                            color: "#4f7cff"
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                color: "#ffffff"
                radius: 12
                border.color: "#d9e0ee"
                Layout.preferredHeight: 64

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 8

                    CheckBox {
                        checked: bridge.movilidadReducida
                        text: "Movilidad reducida"
                        onToggled: bridge.movilidadReducida = checked
                    }
                }
            }

            Item { Layout.fillHeight: true }
        }
    }
}
