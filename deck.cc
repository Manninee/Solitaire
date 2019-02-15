#include "deck.hh"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>
#include <random>
#include <algorithm>

Deck::Deck(QWidget *parent) : QFrame(parent)
{
    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    for (int suit = SPADE; suit != SUIT_COUNT; ++suit){

        for (unsigned value = 1; value <= 13; ++value){
            auto card = new Card(static_cast<CardSuit>(suit), value, this);
            int xOffset = (this->width() - card->width()) / 2;
            int yOffset = (this->height() - card->height()) / 2;
            card->move(xOffset, yOffset);
            cards_.push_back(card);
        }
    }

    // Sekoittaa kortit
    std::srand(time(NULL));
    std::random_shuffle(cards_.begin(), cards_.end());
}

Card* Deck::pickCard()
{
    if (cards_.empty()){
        return nullptr;
    } else {
        Card* card = cards_.back();
        cards_.pop_back();
        return card;
    }
}

void Deck::setOpenDeckPointer(OpenDeck* openDeck)
{
    openDeck_ = openDeck;
}

// Suoritetaan, kun pakkaa klikataan.
void Deck::mousePressEvent(QMouseEvent *event)
{
    // Ohjelma ei saa kaatua tyhjän pakan klikkaukseen.
    if (cards_.empty()){
        return;
    }

    // Otetaan osoittimen päähän pakan päällimmäinen kortti ja poistetaan se pakasta.
    Card* card = cards_.back();
    cards_.pop_back();

    // Ohjelma ei saa kaatua, jos korttia ei olekaan.
    if (!card){
        return;
    }

    // Ilmoitetaan, että pakasta otettiin kortti.
    emit cardPicked(card);

    // Hyväksytään klikkaus, koska se käsitellään aina tässä metodissa.
    event->accept();
}

// Suoritettaan kun pakkaa klikataan kaksi kertaa
void Deck::mouseDoubleClickEvent(QMouseEvent *event)
{
    // Vain jos pakassa ei ole kortteja
    if(cards_.empty())
    {
        // Laittaa kaikki avoimesta pakasta saadut kortit suljettuun pakkaan
        for(Card* card: openDeck_->returnCards())
        {
            card->setParent(this);
            card->turn();
            card->show();
            cards_.push_back(card);
        }
        event->accept();
    }
}
