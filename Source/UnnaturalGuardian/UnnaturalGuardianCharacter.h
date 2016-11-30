// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "UnnaturalGuardianCharacter.generated.h"

UCLASS(config=Game)
class AUnnaturalGuardianCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	virtual void Tick(float DeltaSeconds) override;


public:
	AUnnaturalGuardianCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Sphere Collider */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollider;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float maxHealth_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float playerCurrentHealth_;

	UFUNCTION(BlueprintCallable, category = "Player")
	void enableStealthMode();
	UFUNCTION(BlueprintCallable, category = "Player")
	void disableStealthMode();

	// Call when we press a key (E) to destroy the enemy
	UFUNCTION(BlueprintCallable, category = "Player")
	void destroyEnemy();

	// Call when we press a key (E) to destroy an orb within the collision sphere
	UFUNCTION(BlueprintCallable, category = "Player")
	void destoryOrb();

	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
	void healthChangeEffect();


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void decreasePlayerHealth(float amount);

	UFUNCTION(BlueprintCallable, category = "Player")
	void addPlayerHealth(float amount);

	UFUNCTION(BlueprintCallable, category = "Player")
	float getPlayerCurrentHealth() const { return playerCurrentHealth_; }

	UFUNCTION(BlueprintCallable, category = "Player")
	float getPlayerMaxHealth() const { return maxHealth_; }

	//Returns isStealthed_ bool  
	UFUNCTION(BlueprintPure, Category = "Player")
	bool isPlayerInStealthMode() const { return isStealthed_; };


private:

	bool isStealthed_{ false };

	//Returns the sphereCollider (USphereComponent)
	FORCEINLINE class USphereComponent* GetSphereCollider() const { return SphereCollider; }

};

