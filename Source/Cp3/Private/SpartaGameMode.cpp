#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();

	GameStateClass = ASpartaGameState::StaticClass();
}
