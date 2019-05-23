#include "l2core/network/packets/ServerToNpcPackets.h"

#include <iostream>

// FIXED: custom
std::ostream& operator<<(std::ostream& out, const ServerToNpcPackets packetId)
{
    switch (packetId)
    {
        case ServerToNpcPacket_VersionPacket:
            return out << "VersionPacket";
        case ServerToNpcPacket_CreatePacket:
            return out << "CreatePacket";
        case ServerToNpcPacket_EnterWorldPacket:
            return out << "EnterWorldPacket";
        case ServerToNpcPacket_MovePacket:
            return out << "MovePacket";
        case ServerToNpcPacket_SayPacket:
            return out << "SayPacket";
        case ServerToNpcPacket_AttackPacket:
            return out << "AttackPacket";
        case ServerToNpcPacket_AttackedPacket:
            return out << "AttackedPacket";
        case ServerToNpcPacket_DiePacket:
            return out << "DiePacket";
        case ServerToNpcPacket_TalkPacket:
            return out << "TalkPacket";
        case ServerToNpcPacket_TeleportRequestedEventPacket:
            return out << "TeleportRequestedEventPacket";
        case ServerToNpcPacket_BuyRequestedEventPacket:
            return out << "BuyRequestedEventPacket";
        case ServerToNpcPacket_SellRequestedEventPacket:
            return out << "SellRequestedEventPacket";
        case ServerToNpcPacket_QuestAcceptedEventPacket:
            return out << "QuestAcceptedEventPacket";
        case ServerToNpcPacket_RequestNPCSpawn:
            return out << "RequestNPCSpawn";
        case ServerToNpcPacket_MenuSelectEventPacket:
            return out << "MenuSelectEventPacket";
        case ServerToNpcPacket_ResurrectionPacket:
            return out << "ResurrectionPacket";
        case ServerToNpcPacket_SkillUsePacket:
            return out << "SkillUsePacket";
        case ServerToNpcPacket_CheckMapIndex:
            return out << "CheckMapIndex";
        case ServerToNpcPacket_MoveToPawn:
            return out << "MoveToPawn";
        case ServerToNpcPacket_QuestChoice:
            return out << "QuestChoice";
        case ServerToNpcPacket_SeeCreature:
            return out << "SeeCreature";
        case ServerToNpcPacket_SeeAttack:
            return out << "SeeAttack";
        case ServerToNpcPacket_SeeSpell:
            return out << "SeeSpell";
        case ServerToNpcPacket_OneSkillSelecte:
            return out << "OneSkillSelecte";
        case ServerToNpcPacket_LearnSkillRequest:
            return out << "LearnSkillRequest";
        case ServerToNpcPacket_SkillQuestAccept:
            return out << "SkillQuestAccept";
        case ServerToNpcPacket_SeeItem:
            return out << "SeeItem";
        case ServerToNpcPacket_ClassChangeRequest:
            return out << "ClassChangeRequest";
        case ServerToNpcPacket_FriendAttacked:
            return out << "FriendAttacked";
        case ServerToNpcPacket_TimePacket:
            return out << "TimePacket";
        case ServerToNpcPacket_DeleteNPCPacket:
            return out << "DeleteNPCPacket";
        case ServerToNpcPacket_FinishUseSkill:
            return out << "FinishUseSkill";
        case ServerToNpcPacket_TalkSelect:
            return out << "TalkSelect";
        case ServerToNpcPacket_ClanAttack:
            return out << "ClanAttack";
        case ServerToNpcPacket_SetAI:
            return out << "SetAI";
        case ServerToNpcPacket_TimeHour:
            return out << "TimeHour";
        case ServerToNpcPacket_ClanSpelled:
            return out << "ClanSpelled";
        case ServerToNpcPacket_DesireManipuration:
            return out << "DesireManipuration";
        case ServerToNpcPacket_CreatePledge:
            return out << "CreatePledge";
        case ServerToNpcPacket_DismissPledge:
            return out << "DismissPledge";
        case ServerToNpcPacket_RevivePledge:
            return out << "RevivePledge";
        case ServerToNpcPacket_LevelUpPledge:
            return out << "LevelUpPledge";
        case ServerToNpcPacket_ServerPing:
            return out << "ServerPing";
        case ServerToNpcPacket_SiegeEvent:
            return out << "SiegeEvent";
        case ServerToNpcPacket_HolyThingSpelled:
            return out << "HolyThingSpelled";
        case ServerToNpcPacket_PongForCastleSiege:
            return out << "PongForCastleSiege";
        case ServerToNpcPacket_DeleteHatePacket:
            return out << "DeleteHatePacket";
        case ServerToNpcPacket_DeleteHateOfUserPacket:
            return out << "DeleteHateOfUserPacket";
        case ServerToNpcPacket_RandomizeHatePacket:
            return out << "RandomizeHatePacket";
        case ServerToNpcPacket_ConfusePacket:
            return out << "ConfusePacket";
        case ServerToNpcPacket_RunAwayPacket:
            return out << "RunAwayPacket";
        case ServerToNpcPacket_ContributionWinnerPledgePacket:
            return out << "ContributionWinnerPledgePacket";
        case ServerToNpcPacket_GeneralEventPacket:
            return out << "GeneralEventPacket";
        case ServerToNpcPacket_UserObjectEvent:
            return out << "UserObjectEvent";
        case ServerToNpcPacket_AgitEventPacket:
            return out << "AgitEventPacket";
        case ServerToNpcPacket_TutorialMenuSelectEventPacket:
            return out << "TutorialMenuSelectEventPacket";
        case ServerToNpcPacket_TutorialQuestionMarkClicked:
            return out << "TutorialQuestionMarkClicked";
        case ServerToNpcPacket_TutorialEvent:
            return out << "TutorialEvent";
        case ServerToNpcPacket_CreateAlliance:
            return out << "CreateAlliance";
        case ServerToNpcPacket_ManageCastleSiege:
            return out << "ManageCastleSiege";
        case ServerToNpcPacket_PetAction:
            return out << "PetAction";
        case ServerToNpcPacket_RequestNPCInfo:
            return out << "RequestNPCInfo";
        case ServerToNpcPacket_DoorHpLevelInfo:
            return out << "DoorHpLevelInfo";
        case ServerToNpcPacket_ConrolTowerLevelInfo:
            return out << "ConrolTowerLevelInfo";
        case ServerToNpcPacket_NpcDoNothing:
            return out << "NpcDoNothing";
    }

    return out << "INVALID PACKET ID " << (int)packetId;
}
