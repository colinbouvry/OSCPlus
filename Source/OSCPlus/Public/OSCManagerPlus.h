// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OSCManager.h"
#include "OSCManagerPlus.generated.h"

/**
 * 
 */
UCLASS()
class OSCPLUS_API UOSCManagerPlus : public UOSCManager
{
	GENERATED_BODY()

	/** Set Value to integer at provided Index in OSCMessage if in bounds and type matches */
	UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Get OSC Message Double at Index", Keywords = "osc message"))
	static UPARAM(DisplayName = "Succeeded") bool GetDouble(const FOSCMessage& Message, const int32 Index, double& Value);

	/** Adds double value to end of OSCMessage */
	UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Add Float to OSC Message", Keywords = "osc message"))
	static UPARAM(DisplayName = "Message") FOSCMessage& AddDouble(UPARAM(ref) FOSCMessage& Message, double Value);

	UFUNCTION(BlueprintCallable, Category = "Audio|OSC", meta = (DisplayName = "Create OSCMessage from Bytes", Keywords = "osc message"))
	static FOSCMessage& CreateOSCMessageFromBytes(const TArray<uint8>& ByteData);
};
