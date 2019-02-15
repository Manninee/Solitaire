#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include "deck.hh"
#include "opendeck.hh"
#include "gamerules.hh"
#include "cardslot.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Antaa opendeckin osoittimen
    OpenDeck* getOpenDeckPointer();

private slots:
    // Slotti voiton tarkistusta varten
    void winStatus(bool status);

    // Slotti lopetusnappia varten
    void quitButton();

private:
    void setupLayout();
    void setupSlots();

    // Voittoruudun toteuttus
    void winScreen();

    // Talletetaan attribuuteiksi ne widgetit, joita saattaa tarvita käsitellä pelin aikana.
    Deck* deck_;
    OpenDeck* pickedCards_;
    std::vector<CardSlot*> cardSlots_;
    std::vector<CardSlot*> suitSlots_;

    // Valmiiden suitSlottien määrä
    unsigned int completeSlots_;

    // Osoittimet ylä- ja alarivilayoutteihin
    QHBoxLayout* bottomRowLayout_;
    QHBoxLayout* topRowLayout_;

    // Pelin aloitusaika
    unsigned long long int startTime_;
};

#endif // MAINWINDOW_HH
