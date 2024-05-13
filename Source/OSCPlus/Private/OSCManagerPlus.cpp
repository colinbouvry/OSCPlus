// Fill out your copyright notice in the Description page of Project Settings.

#include "OSCManagerPlus.h"
#include "OSCMessage.h"
#include "OSCLog.h"
#include "OSCMessagePacket.h"

DEFINE_LOG_CATEGORY(LogOSC);
#define OSC_LOG_INVALID_TYPE_AT_INDEX(TypeStr, Index, Msg) UE_LOG(LogOSC, Warning, TEXT("OSC Message Parse Failed: OSCType not %s: index '%i', OSCAddress '%s'"), TypeStr, Index, *Msg.GetAddress().GetFullPath())

namespace OSC
{
	const FOSCType* GetOSCTypeAtIndex(const FOSCMessage& InMessage, const int32 InIndex)
	{
		const TSharedPtr<FOSCMessagePacket>& Packet = StaticCastSharedPtr<FOSCMessagePacket>(InMessage.GetPacket());
		if (Packet.IsValid())
		{
			TArray<FOSCType>& Args = Packet->GetArguments();
			if (InIndex >= Args.Num())
			{
				UE_LOG(LogOSC, Warning, TEXT("Index '%d' out-of-bounds.  Message argument size = '%d'"), InIndex, Args.Num());
				return nullptr;
			}

			return &Args[InIndex];
		}

		return nullptr;
	}
} // namespace OSC

bool UOSCManagerPlus::GetDouble(const FOSCMessage& InMessage, const int32 InIndex, double& OutValue)
{
	OutValue = 0;
	if (const FOSCType* OSCType = OSC::GetOSCTypeAtIndex(InMessage, InIndex))
	{
		if (OSCType->IsDouble())
		{
			OutValue = OSCType->GetDouble();
			return true;
		}
		OSC_LOG_INVALID_TYPE_AT_INDEX(TEXT("Double"), InIndex, InMessage);
	}

	return false;
}

FOSCMessage& UOSCManagerPlus::AddDouble(FOSCMessage& OutMessage, double InValue)
{
	const TSharedPtr<FOSCMessagePacket>& MessagePacket = StaticCastSharedPtr<FOSCMessagePacket>(OutMessage.GetPacket());
	MessagePacket->GetArguments().Add(FOSCType(InValue));
	return OutMessage;
}

FOSCMessage& UOSCManagerPlus::CreateOSCMessageFromBytes(const TArray<uint8>& ByteData)
{
	FOSCStream Stream(ByteData.GetData(), ByteData.GetAllocatedSize());
	TSharedPtr<FOSCMessagePacket> MessagePacket = MakeShared<FOSCMessagePacket>();
	MessagePacket->ReadData(Stream);
	static FOSCMessage Message(MessagePacket);
	return Message;
}