#include "ScopeDialog.h"
#include "ui_ScopeDialog.h"

#include "lib/common/utils.h"

ScopeDialog::ScopeDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ScopeDialog)
{
  ui->setupUi(this);

  ui->EnergySlider->setValue(int(Ecm*GeV2TeV));

  ui->ScaleComboBox1->addItem("transverse momentum of produced particle");
  ui->ScaleComboBox1->addItem("transverse mass of produced particle");
  ui->ScaleComboBox1->addItem("total energy of partonic subprocess");
  if (Factorization == TMD)
    ui->ScaleComboBox1->addItem("total energy of partonic subprocess plus incoming parton pair transverse momentum");

  ui->ScaleComboBox2->addItem("transverse momentum of produced particle");
  ui->ScaleComboBox2->addItem("transverse mass of produced particle");
  ui->ScaleComboBox2->addItem("total energy of partonic subprocess");
  if (Factorization == TMD)
    ui->ScaleComboBox2->addItem("total energy of partonic subprocess plus incoming parton pair transverse momentum");

  switch (RenormalizationScale)
  {
    case FinalParticleTransverseMomentum:            ui->ScaleComboBox1->setCurrentIndex(0);
                                                     break;
    case FinalParticleTransverseMass:                ui->ScaleComboBox1->setCurrentIndex(1);
                                                     break;
    case SubprocessEnergy:                           ui->ScaleComboBox1->setCurrentIndex(2);
                                                     break;
    case SubprocessEnergyPlusPairTransverseMomentum: ui->ScaleComboBox1->setCurrentIndex(3);
                                                     break;
  }

  switch (FactorizationScale)
  {
    case FinalParticleTransverseMomentum:            ui->ScaleComboBox2->setCurrentIndex(0);
                                                     break;
    case FinalParticleTransverseMass:                ui->ScaleComboBox2->setCurrentIndex(1);
                                                     break;
    case SubprocessEnergy:                           ui->ScaleComboBox2->setCurrentIndex(2);
                                                     break;
    case SubprocessEnergyPlusPairTransverseMomentum: ui->ScaleComboBox2->setCurrentIndex(3);
                                                     break;
  }

  if ( (PDF == AZERO) or (PDF == JH2013set1) or (PDF == JH2013set2) )
    ui->ScaleComboBox2->setDisabled(true);

  switch (ScaleRate)
  {
    case LowerScale:   ui->ScaleRateSlider->setValue(0);
                       break;
    case DefaultScale: ui->ScaleRateSlider->setValue(1);
                       break;
    case UpperScale:   ui->ScaleRateSlider->setValue(2);
                       break;
  }

  ui->MCSpinBox1->setValue(nIterations);
  ui->MCSpinBox2->setValue(nEventsPerIteration);
}

ScopeDialog::~ScopeDialog()
{
  delete ui;
}

void ScopeDialog::setToStock(void)
{
  Ecm = (ui->EnergySlider->value())*TeV2GeV;

  switch (ui->ScaleComboBox1->currentIndex())
  {
    case 0: RenormalizationScale = FinalParticleTransverseMomentum;
            break;
    case 1: RenormalizationScale = FinalParticleTransverseMass;
            break;
    case 2: RenormalizationScale = SubprocessEnergy;
            break;
    case 3: RenormalizationScale = SubprocessEnergyPlusPairTransverseMomentum;
            break;
  }

  switch (ui->ScaleComboBox2->currentIndex())
  {
    case 0: FactorizationScale = FinalParticleTransverseMomentum;
            break;
    case 1: FactorizationScale = FinalParticleTransverseMass;
            break;
    case 2: FactorizationScale = SubprocessEnergy;
            break;
    case 3: FactorizationScale = SubprocessEnergyPlusPairTransverseMomentum;
            break;
  }

  switch (ui->ScaleRateSlider->value())
  {
    case 0: ScaleRate = LowerScale;
            break;
    case 1: ScaleRate = DefaultScale;
            break;
    case 2: ScaleRate = UpperScale;
            break;
  }

  nIterations = ui->MCSpinBox1->value();
  nEventsPerIteration = ui->MCSpinBox2->value();
}
