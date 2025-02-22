void ASpartaCharacter::UpdateOverheadHP()
{
	if (!OverheadWidget)
	{
		return;
	}

	if (UUserWidget* WidgetInstance = OverheadWidget->GetUserWidgetObject())
	{
		if (UProgressBar* HPBar = Cast<UProgressBar>(WidgetInstance->GetWidgetFromName(TEXT("HealthBar"))))
		{
			const float HPPercent = (MaxHealth > 0.f) ? Health / MaxHealth : 0.f;
			HPBar->SetPercent(HPPercent);

			// HP�� ���� �� ���� ����
			if (HPPercent < 0.3f)
			{
				HPBar->SetFillColorAndOpacity(FLinearColor::Red);
			}
		}
	}
}