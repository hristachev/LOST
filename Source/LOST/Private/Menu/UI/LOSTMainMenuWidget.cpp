// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Menu/UI/LOSTMainMenuWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ULOSTMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ULOSTMainMenuWidget::OnStartGame);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &ULOSTMainMenuWidget::OnSettings);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &ULOSTMainMenuWidget::OnQuitGame);
	}
}

void ULOSTMainMenuWidget::OnStartGame()
{
	const auto LevelName = "TestLevel";
	UGameplayStatics::OpenLevel(this, LevelName);
}

void ULOSTMainMenuWidget::OnSettings()
{
	if(!LanguageBox) return;
	LanguageBox->ClearChildren();
	
	if (SettingsWidgetClass)
	{
		const auto SettingsWidget = CreateWidget<UUserWidget>(GetWorld(), SettingsWidgetClass);
		if (SettingsWidget)
		{
			if (!IsSettingsVisible)
			{
				LanguageBox->AddChild(SettingsWidget);
				LanguageBox->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				LanguageBox->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	IsSettingsVisible = !IsSettingsVisible;
}

void ULOSTMainMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
