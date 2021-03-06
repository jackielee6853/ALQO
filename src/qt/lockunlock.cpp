// Copyright (c) 2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/lockunlock.h"
#include "qt/forms/ui_lockunlock.h"

LockUnlock::LockUnlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LockUnlock)
{
    ui->setupUi(this);

    // Load css.
    this->setStyleSheet(parent->styleSheet());

    ui->container->setProperty("cssClass", "top-sub-menu");

    //ui->pushButtonUnlocked->setProperty("cssClass", "btn-check-lock-sub-menu-unlocked");
    //ui->pushButtonLocked->setProperty("cssClass", "btn-check-lock-sub-menu-locked");
    //ui->pushButtonStaking->setProperty("cssClass", "btn-check-lock-sub-menu-staking");

    ui->pushButtonUnlocked->setText(tr("Unlock"));
    ui->pushButtonLocked->setText(tr("Lock"));
    ui->pushButtonStaking->setText(tr("Staking"));

    // Connect
    connect(ui->pushButtonUnlocked, SIGNAL(clicked()), this, SLOT(onUnlockClicked()));
    connect(ui->pushButtonLocked, SIGNAL(clicked()), this, SLOT(onLockClicked()));
    connect(ui->pushButtonStaking, SIGNAL(clicked()), this, SLOT(onStakingClicked()));
}

LockUnlock::~LockUnlock()
{
    delete ui;
}

void LockUnlock::updateStatus(WalletModel::EncryptionStatus status){
    switch (status){
        case WalletModel::EncryptionStatus::Unlocked:
            ui->pushButtonUnlocked->setChecked(true);
            ui->pushButtonLocked->setChecked(false);
            ui->pushButtonStaking->setChecked(false);
            break;
        case WalletModel::EncryptionStatus::UnlockedForAnonymizationOnly:
            ui->pushButtonUnlocked->setChecked(false);
            ui->pushButtonLocked->setChecked(false);
            ui->pushButtonStaking->setChecked(true);
            break;
        case WalletModel::EncryptionStatus::Locked:
            ui->pushButtonUnlocked->setChecked(false);
            ui->pushButtonLocked->setChecked(true);
            ui->pushButtonStaking->setChecked(false);
            break;
        default:
            break;
    }
}

void LockUnlock::onLockClicked(){
    lock = 0;
    emit lockClicked(StateClicked::LOCK);
}

void LockUnlock::onUnlockClicked(){
    lock = 1;
    emit lockClicked(StateClicked::UNLOCK);
}

void LockUnlock::onStakingClicked(){
    lock = 2;
    emit lockClicked(StateClicked::UNLOCK_FOR_STAKING);
}

void LockUnlock::enterEvent(QEvent *)
{
    isOnHover = true;
    emit Mouse_Entered();
}

void LockUnlock::leaveEvent(QEvent *)
{
    isOnHover = false;
    emit Mouse_Leave();
}

bool LockUnlock::isHovered(){
    return isOnHover;
}
