import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Rectangle {
    id: root
    color: "#0f1115"
    radius: 14

    Material.theme: Material.Dark
    Material.accent: "#6ea0ff"

    property var pisos: ["Universidad", "Piso 1", "Piso 2", "Piso 3", "Piso 4", "Piso 5"]
    property var perfiles: ["Regular", "Nuevo"]

    ScrollView {
        anchors.fill: parent
        padding: 16
        clip: true

        ColumnLayout {
            width: parent.width - 8
            spacing: 14

            Rectangle {
                Layout.fillWidth: true
                color: "#171b22"
                radius: 12
                border.color: "#2a2f3a"
                implicitHeight: 64

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 10

                    Rectangle {
                        width: 10
                        height: 36
                        radius: 6
                        color: "#6ea0ff"
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "EcoCampus"
                            font.pixelSize: 18
                            font.bold: true
                            color: "#f4f6fb"
                        }
                        Text {
                            text: "Control de recorridos"
                            font.pixelSize: 12
                            color: "#9aa6c3"
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                color: "#171b22"
                radius: 12
                border.color: "#2a2f3a"
                Layout.preferredHeight: 160

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    Text {
                        text: "Mapa"
                        font.pixelSize: 13
                        color: "#9aa6c3"
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
                color: "#171b22"
                radius: 12
                border.color: "#2a2f3a"
                Layout.preferredHeight: 160

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    Text {
                        text: "Inicio"
                        font.pixelSize: 13
                        color: "#9aa6c3"
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
                color: "#171b22"
                radius: 12
                border.color: "#2a2f3a"
                Layout.preferredHeight: 110

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 6

                    Text {
                        text: "Resultados"
                        font.pixelSize: 13
                        color: "#9aa6c3"
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Tiempo"
                            color: "#f4f6fb"
                            font.pixelSize: 13
                        }
                        Item { Layout.fillWidth: true }
                        Text {
                            text: bridge.tiempo
                            color: "#6ea0ff"
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Visitados"
                            color: "#f4f6fb"
                            font.pixelSize: 13
                        }
                        Item { Layout.fillWidth: true }
                        Text {
                            text: bridge.visitados
                            color: "#6ea0ff"
                            font.pixelSize: 13
                            font.bold: true
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                color: "#171b22"
                radius: 12
                border.color: "#2a2f3a"
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

            Rectangle {
                Layout.fillWidth: true
                color: "#171b22"
                radius: 12
                border.color: "#2a2f3a"
                Layout.preferredHeight: 200

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    Text {
                        text: "Ruta entre puntos"
                        font.pixelSize: 13
                        color: "#9aa6c3"
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        ColumnLayout {
                            Layout.fillWidth: true
                            Text { text: "Origen"; font.pixelSize: 12; color: "#9aa6c3" }
                            SpinBox {
                                from: 1
                                value: bridge.origen
                                editable: true
                                Layout.fillWidth: true
                                implicitHeight: 36
                                onValueChanged: {
                                    if (bridge.origen !== value)
                                        bridge.origen = value
                                }
                            }
            Item { Layout.fillHeight: true }
                        }

                        ColumnLayout {
                            Layout.fillWidth: true
                            Text { text: "Destino"; font.pixelSize: 12; color: "#9aa6c3" }
                            SpinBox {
                                from: 1
                                value: bridge.destino
                                editable: true
                                Layout.fillWidth: true
                                implicitHeight: 36
                                onValueChanged: {
                                    if (bridge.destino !== value)
                                        bridge.destino = value
                                }
                            }
                        }
                    }

                    ComboBox {
                        model: perfiles
                        Layout.fillWidth: true
                        currentIndex: perfiles.indexOf(bridge.perfilRuta)
                        onCurrentTextChanged: bridge.perfilRuta = currentText
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        Button {
                            text: "Buscar camino"
                            Layout.fillWidth: true
                            implicitHeight: 36
                            onClicked: bridge.requestBuscarCamino()
                        }

                        Button {
                            text: "Ruta por perfil"
                            Layout.fillWidth: true
                            implicitHeight: 36
                            onClicked: bridge.requestRutaPerfil()
                        }
                    }
                }
            }
        }
    }
}
