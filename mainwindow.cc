#include <QFrame>
#include <QHBoxLayout>

#include "mainwindow.hh"
#include "cardslot.hh"

unsigned const int SUITSLOTS = 4;
unsigned const int CARDSLOTS = 8;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      completeSlots_(0)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setupLayout();
    this->setStyleSheet("background-color:grey;");
    connect(deck_, &Deck::cardPicked, pickedCards_, &OpenDeck::addCard);

    // Yhdistetään voitontarkistukseen tarvittavan signaalit
    for(CardSlot* suitSlot: suitSlots_)
    {
        connect(suitSlot, &CardSlot::slotStatus, this, &MainWindow::winStatus);
    }

    // Otetaan aloitusaika talteen
    startTime_ = time(NULL);
}

MainWindow::~MainWindow()
{
    for(CardSlot* cardSlot: suitSlots_)
    {
        delete cardSlot;
    }
    for(CardSlot* cardSlot: cardSlots_)
    {
        delete cardSlot;
    }
    delete deck_;
    delete pickedCards_;
}

OpenDeck *MainWindow::getOpenDeckPointer()
{
    return pickedCards_;
}

void MainWindow::setupLayout()
{
    // Pääikkunan isoimpana rakenteena on frame, joka sisältää...
    QFrame* frame = new QFrame;
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    // ... alarivin ja ylärivin.
    bottomRowLayout_ = new QHBoxLayout();
    topRowLayout_ = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout_);
    frameLayout->addLayout(bottomRowLayout_);

    // Luodaan pakkaoliot.
    deck_ = new Deck(this);
    pickedCards_ = new OpenDeck(this);

    deck_->setOpenDeckPointer(pickedCards_);

    // Lisätään yläriville suljettu ja avoin pakka...
    topRowLayout_->addWidget(deck_);
    topRowLayout_->addWidget(pickedCards_);

    // Lisää yläriville tyhjän tilan keskelle
    topRowLayout_->addStretch();

    setupSlots();

    setCentralWidget(frame);
}

void MainWindow::setupSlots()
{
    // Lisätään yläriville neljä cardslottia
    for(unsigned int i = 0; i < SUITSLOTS; ++i)
    {
        CardSlot* tempCardSlot = new CardSlot(&GameRules::checkSuitSlot, this, true);
        suitSlots_.push_back(tempCardSlot);
        topRowLayout_->addWidget(tempCardSlot);
    }

    // ... ja alariville kahdeksan cardslottia.
    for(unsigned int i = 0; i < CARDSLOTS; ++i)
    {
        CardSlot* tempCardSlot = new CardSlot(&GameRules::checkCard, this);

        // Ja jokaiseen cardslottiin alkukortit
        for(unsigned int e = 0; e <= i; ++e)
        {
            Card* tempCard = deck_->pickCard();
            tempCardSlot->addCard(tempCard);

            // Jos kortti on päälimmäinen niin käännetään se
            if(e == i)
            {
                tempCard->turn();
                tempCard->allowOpen();
            }
        }
        cardSlots_.push_back(tempCardSlot);
        bottomRowLayout_->addWidget(tempCardSlot);
    }
}

void MainWindow::winScreen()
{
    // Poistetaan kaikki cardslotit ja pakat
    for(CardSlot* cardSlot: cardSlots_)
    {
        cardSlot->close();
    }
    for(CardSlot* cardSlot: suitSlots_)
    {
        cardSlot->close();
    }
    deck_->close();
    pickedCards_->close();

    // Lasketaan kulunutaika
    unsigned long int totalTime = time(NULL) - startTime_;
    unsigned int minutes = totalTime / 60;
    unsigned int seconds = totalTime % 60;


    // Luodaan teksti napille jossa kerrotaan kulunut aika
    std::string buttonText = "Voitit pelin!!!\n Sinulla meni " +
            std::to_string(minutes) + " minutttia ja " +
            std::to_string(seconds) + " sekuntia.";

    // Luodaan uusi nappi ja asetetaan se koko ruudun kokoiseksi
    QPushButton* pushButton = new QPushButton(QString::fromStdString(buttonText), this);
    pushButton->setFont(QFont ("Helvetica", 20, QFont::Bold));
    pushButton->setStyleSheet("background-color:grey;");
    connect(pushButton, SIGNAL (released()), this, SLOT (quitButton()));
    pushButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bottomRowLayout_->addWidget(pushButton);
}

// Saa parametrina onko suitslotti valmis
void MainWindow::winStatus(bool status)
{
    completeSlots_ += status;
    if(completeSlots_ == SUITSLOTS)
    {
        winScreen();
    }
}

void MainWindow::quitButton()
{
    this->close();
}
