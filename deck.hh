#ifndef DECK_HH
#define DECK_HH

#include <vector>
#include <QFrame>
#include "card.hh"
#include "opendeck.hh"

class Deck : public QFrame
{
    Q_OBJECT

public:
    Deck(QWidget *parent = 0);

    // Korttipakasta voi nostaa päällimmäisen kortin.
    Card* pickCard();
    void setOpenDeckPointer(OpenDeck* openDeck);

signals:
    // Signaali, jonka pakka lähettää, kun kortti nostetaan.
    void cardPicked(Card* card);

protected:
    // Itse toteutettu Qt:n widgetin klikkaamiseen liittyvä metodi.
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    // Korttipakan sisältämät kortit.
    std::vector<Card*> cards_;

    // Osoitin suljettuun pakkaan
    OpenDeck* openDeck_;
};

#endif // DECK_HH
