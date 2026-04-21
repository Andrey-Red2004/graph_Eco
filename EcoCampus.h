#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QHash>
#include <QObject>
#include <QString>
#include "ui_EcoCampus.h"
#include "CampusController.h"
#include <vector>

class UiBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int inicio READ inicio WRITE setInicio NOTIFY inicioChanged)
    Q_PROPERTY(QString tiempo READ tiempo WRITE setTiempo NOTIFY tiempoChanged)
    Q_PROPERTY(QString visitados READ visitados WRITE setVisitados NOTIFY visitadosChanged)
    Q_PROPERTY(bool movilidadReducida READ movilidadReducida WRITE setMovilidadReducida NOTIFY movilidadReducidaChanged)
    Q_PROPERTY(QString pisoActual READ pisoActual WRITE setPisoActual NOTIFY pisoActualChanged)
    Q_PROPERTY(bool mostrarBiblioteca READ mostrarBiblioteca WRITE setMostrarBiblioteca NOTIFY mostrarBibliotecaChanged)
    Q_PROPERTY(bool mostrarComedor READ mostrarComedor WRITE setMostrarComedor NOTIFY mostrarComedorChanged)

public:
    explicit UiBridge(QObject* parent = nullptr);

    int inicio() const { return inicio_; }
    void setInicio(int value);

    QString tiempo() const { return tiempo_; }
    void setTiempo(const QString& value);

    QString visitados() const { return visitados_; }
    void setVisitados(const QString& value);

    bool movilidadReducida() const { return movilidadReducida_; }
    void setMovilidadReducida(bool value);

    QString pisoActual() const { return pisoActual_; }
    void setPisoActual(const QString& value);

    bool mostrarBiblioteca() const { return mostrarBiblioteca_; }
    void setMostrarBiblioteca(bool value);

    bool mostrarComedor() const { return mostrarComedor_; }
    void setMostrarComedor(bool value);

    Q_INVOKABLE void requestDfs();
    Q_INVOKABLE void requestBfs();

signals:
    void inicioChanged();
    void tiempoChanged();
    void visitadosChanged();
    void movilidadReducidaChanged(bool enabled);
    void pisoActualChanged();
    void mostrarBibliotecaChanged();
    void mostrarComedorChanged();
    void dfsRequested();
    void bfsRequested();

private:
    int inicio_ = 1;
    QString tiempo_ = QStringLiteral("0 µs");
    QString visitados_ = QStringLiteral("0");
    bool movilidadReducida_ = false;
    QString pisoActual_ = QStringLiteral("Universidad");
    bool mostrarBiblioteca_ = false;
    bool mostrarComedor_ = false;
};

class EcoCampus : public QMainWindow
{
    Q_OBJECT

public:
    EcoCampus(QWidget *parent = nullptr);
    ~EcoCampus();

private:
    Ui::EcoCampusClass ui;
    CampusController controller_;
    QGraphicsScene* scene_ = nullptr;
    std::vector<int> rutaActual_;
    bool updatePending_ = false;
    bool panning_ = false;
    QPoint lastPanPos_;
    UiBridge* uiBridge_ = nullptr;
    QHash<QString, QGraphicsPixmapItem*> mapLayers_;

    void dibujarGrafo();
    void configurarInteraccionVista();
    void configurarPanelQml();
    void actualizarCapasMapa();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void on_btnDFS_clicked();
    void on_btnBFS_clicked();
    void on_chkMovilidad_stateChanged(int state);
    void onSceneSelectionChanged();
    void onMovilidadChanged(bool enabled);
};

