#include "pch.h"
#include "LevelScene.h"

LevelScene::LevelScene(std::string id, Camera* c, World* w) : Scene(id, c, w)
{
    betTotal = 0;

    deck = new Deck();

    bg = new Image("bg", "images/bg.png", 0.0f, 0.0f);
    chipbg = new Image("chipbg", "images/chipbg.png", 1025.0f, 0.0f);
    table = new Image("table", "images/table.png", 0.0f, 0.0f);

    dealerLabel = new Text("dealerLabel", "fonts/ds-digit.ttf", "DEALER", 5.0f, 10.0f, 70, { 255, 255, 0, 255 });
    playerLabel = new Text("playerLabel", "fonts/ds-digit.ttf", "PLAYER", 5.0f, 250.0f, 70, { 255, 255, 0, 255 });
    dealerLabel->setVisible(false);
    playerLabel->setVisible(false);

    wallet = new Wallet("wallet", 425.0f, 10.0f, 10000);
    bank = new Bank("chip", "images/CHIPS.png", 1050.0f, 20.0f, 2, 5, wallet);
    bank->setWallet(wallet);
    bank->setActive(false);
    wallet->setVisible(false);

    playBtn = new Button("play", "images/buttons.png", 50.0f, 680.0f, 1, 7);
    betBtn = new Button("bet", "images/buttons.png", 50.0f, 680.0f, 1, 7);
    hitBtn = new Button("hit", "images/buttons.png", 200.0f, 680.0f, 1, 7);
    standBtn = new Button("stand", "images/buttons.png", 350.0f, 680.0f, 1, 7);
    ddownBtn = new Button("ddown", "images/buttons.png", 500.0f, 680.0f, 1, 7);
    splitBtn = new Button("split", "images/buttons.png", 650.0f, 680.0f, 1, 7);
    quitBtn = new Button("quit", "images/buttons.png", 800.0f, 680.0f, 1, 7);

    playBtn->addFrame("play", 0, 134, 48, 1, 7);
    betBtn->addFrame("bet", 4, 134, 48, 1, 7);
    hitBtn->addFrame("hit", 2, 134, 48, 1, 7);
    standBtn->addFrame("stand", 3, 134, 48, 1, 7);
    ddownBtn->addFrame("ddown", 5, 134, 48, 1, 7);
    splitBtn->addFrame("split", 6, 134, 48, 1, 7);
    quitBtn->addFrame("quit", 1, 134, 48, 1, 7);
}

void LevelScene::onEnter()
{
    addGameObject(bg, 0);
    addGameObject(chipbg, 0);
    addGameObject(table, 1);
    addGameObject(playBtn, 2);
    addGameObject(betBtn, 2);
    addGameObject(hitBtn, 2);
    addGameObject(standBtn, 2);
    addGameObject(ddownBtn, 2);
    addGameObject(splitBtn, 2);
    addGameObject(quitBtn, 2);
    addGameObject(dealerLabel, 2);
    addGameObject(playerLabel, 2);
    addGameObject(bank, 2);
    addGameObject(wallet, 2);

    addEventListener(KeyboardEvent::KEYDOWN, this, &LevelScene::onKeyDown);
    addEventListener(Button::PRESSED, this, &LevelScene::onButtonPressed);

    displayButtons(true, false, false, false, false, false);
}

void LevelScene::onExit()
{
    removeEventListener(KeyboardEvent::KEYDOWN, this, &LevelScene::onKeyDown);
    removeEventListener(Button::PRESSED, this, &LevelScene::onButtonPressed);

    delete deck;
}

void LevelScene::update(float delta)
{
    Scene::update(delta);
}

void LevelScene::render() 
{
    Scene::render();
}

void LevelScene::onKeyDown(const KeyboardEvent& e) 
{
    if (e.key.code == Key::Code::Q) 
    {
        Game::stop();
    }
}

void LevelScene::onButtonPressed(const UserEvent& e)
{
    std::string* buttonType = static_cast<std::string*>(e.getData1());

    if (*buttonType == "play" && playBtn->isVisible())
    {
        LOG_INFO("PLAY Pressed");
        play();
    }
    else if(*buttonType == "bet" && betBtn->isVisible())
    { 
        LOG_INFO("BET Pressed");
        bet();
    }
    else if (*buttonType == "hit" && hitBtn->isVisible())
    {
        LOG_INFO("HIT Pressed");
        hit();
    }
    else if (*buttonType == "stand" && standBtn->isVisible())
    {
        LOG_INFO("STAND Pressed");
        stand();
    }
    else if (*buttonType == "ddown" && ddownBtn->isVisible())
    {
        LOG_INFO("DOUBLE DOWN Pressed");
        doubleDown();
    }
    else if (*buttonType == "split" && splitBtn->isVisible())
    {
        LOG_INFO("SPLIT Pressed");
        split();
    }
    else if (*buttonType == "quit" && quitBtn->isVisible())
    {
        LOG_INFO("QUIT Pressed");
        Game::stop();
    }
}

void LevelScene::displayButtons(bool p, bool b, bool h, bool s, bool d, bool sp)
{
    playBtn->setVisible(p);
    betBtn->setVisible(b);
    hitBtn->setVisible(h);
    standBtn->setVisible(s);
    ddownBtn->setVisible(d);
    splitBtn->setVisible(sp);
}

void LevelScene::startGame()
{
    betTotal = 0;
    currentHand = 0;

    for (auto card : dealerHand.getCards())
    {
        card->setVisible(false);
        removeGameObject(card);
    }

    for (auto hand : playerHands)
    {
        for (auto card : hand.getCards())
        {
            card->setVisible(false);
            removeGameObject(card);
        }

        hand.clear();
    }

    dealerHand.clear();
    playerHands.clear();

    dealerLabel->setText("DEALER");
    playerLabel->setText("PLAYER");
    dealerLabel->setVisible(true);
    playerLabel->setVisible(true);

    wallet->setVisible(true);
    bank->reset();
    bank->setActive(true);

    displayButtons(false, true, false, false, false, false);

    deck->shuffle();
}

void LevelScene::startRound()
{
    Hand playerHand;

    Card* card = deck->dealCard();
    card->setPosition(10.0f, 320.0f);
    addGameObject(card, 3);
    playerHand.addCard(card);

    card = deck->dealCard();
    card->setPosition(10.0f, 80.0f);
    addGameObject(card, 3);
    dealerHand.addCard(card);

    card = deck->dealCard();
    card->setPosition(160.0f, 320.0f);
    addGameObject(card, 3);
    playerHand.addCard(card);

    card = deck->dealCard();
    card->setPosition(160.0f, 80.0f);
    addGameObject(card, 3);
    dealerHand.addCard(card);

    playerHands.push_back(playerHand);
}

void LevelScene::play()
{
    startGame();
}

void LevelScene::postAction(bool standing)
{
    Card* dsc = dealerHand.getCards().at(1);
    dsc->setFrame(dsc->getObjectID());

    if (playerHands[currentHand].getValue() == 21)
    {
        if (dealerHand.getValue() != 21)
        {
            // blackjack
            LOG_INFO("Blackjack");
            wallet->setTotal(wallet->getTotal() + bank->getTotal() + betTotal);
            bank->reset();
        }
        else
        {
            // 21 stand off
            LOG_INFO("Stand-off");
            wallet->setTotal(wallet->getTotal() + bank->getTotal());
            bank->reset();
        }

        displayButtons(true, false, false, false, false, false);
        return;
    }

    if (playerHands[currentHand].getValue() > 21)
    {
        // bust
        LOG_INFO("Bust");
        bank->reset();
        displayButtons(true, false, false, false, false, false);
        return;
    }

    if (standing && dealerHand.getValue() > playerHands[currentHand].getValue())
    {
        // loss
        LOG_INFO("Loss");
        bank->reset();
        displayButtons(true, false, false, false, false, false);
        return;
    }

    if (dealerHand.getValue() < 17)
    {
        Card* card = deck->dealCard();
        card->setPosition(10.0f + 150.0f * dealerHand.size(), 80.0f);
        card->setFrame(card->getObjectID());
        addGameObject(card, 3);
        dealerHand.addCard(card);

        if (dealerHand.getValue() > 21)
        {
            // dealer bust
            LOG_INFO("Dealer bust");
            wallet->setTotal(wallet->getTotal() + bank->getTotal() + betTotal);
            bank->reset();
            displayButtons(true, false, false, false, false, false);
            return;
        }
    }
    else
    {
        if (playerHands[currentHand].getValue() > dealerHand.getValue())
        {
            // win
            LOG_INFO("Win");
            wallet->setTotal(wallet->getTotal() + bank->getTotal() + betTotal);
            bank->reset();
            displayButtons(true, false, false, false, false, false);
            return;
        }

        if (standing && dealerHand.getValue() == playerHands[currentHand].getValue())
        {
            // stand off
            LOG_INFO("Stand-off");
            wallet->setTotal(wallet->getTotal() + bank->getTotal());
            bank->reset();
            displayButtons(true, false, false, false, false, false);
            return;
        }
    }

    displayButtons(false, false, true, true, false, false);
}

void LevelScene::bet()
{
    if (bank->getTotal() < 2 || bank->getTotal() > 500) return;

    int credits = wallet->getTotal();

    bank->setActive(false);
    betTotal = bank->getTotal();

    startRound();

    for (auto card : playerHands[currentHand].getCards())
        card->setFrame(card->getObjectID());

    Card* dfc = dealerHand.getCards()[0];
    dfc->setFrame(dfc->getObjectID());

    Card* dsc = dealerHand.getCards()[1];

    if (dfc->getValue() >= 10)
    {
        dsc->setFrame(dsc->getObjectID());
    }

    if (playerHands[currentHand].getValue() == 21 && dealerHand.getValue() == 21)
    {
        // stand off
        LOG_INFO("Stand-off");
        dsc->setFrame(dsc->getObjectID());
        wallet->setTotal(wallet->getTotal() + bank->getTotal());
        bank->reset();
        displayButtons(true, false, false, false, false, false);
        return;
    }

    if (playerHands[currentHand].getValue() == 21)
    {
        // natural
        LOG_INFO("Natural");
        wallet->setTotal(wallet->getTotal() + bank->getTotal() + betTotal * 0.5f);
        bank->reset();
        displayButtons(true, false, false, false, false, false);
        return;
    }

    bool canDoubleDown = wallet->getTotal() > betTotal && playerHands[currentHand].getValue() <= 11;

    displayButtons(false, false, true, true, canDoubleDown, false);
}

void LevelScene::hit()
{
    Card* card = deck->dealCard();
    card->setPosition(10.0f + 150.0f * playerHands[currentHand].size(), 320.0f);
    card->setFrame(card->getObjectID());
    addGameObject(card, 3);
    playerHands[currentHand].addCard(card);

    postAction();
}

void LevelScene::doubleDown()
{
    wallet->setTotal(wallet->getTotal() - betTotal);
    bank->setTotal(bank->getTotal() + betTotal);
    betTotal += betTotal;

    hit();
}

void LevelScene::stand()
{
    postAction(true);
}

void LevelScene::split()
{

}

void LevelScene::drawCard()
{
    Card* card = deck->dealCard();
    card->setPosition(10 + (playerOffsetX * playerHands[currentHand].getCards().size()), 320.0f);
    card->setFrame(card->getObjectID());
    playerHands[currentHand].addCard(card);
    addGameObject(card, 3);
}

void LevelScene::dealDealer()
{
    
}
