/* $Id$ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file command_func.h Functions related to commands. */

#ifndef COMMAND_FUNC_H
#define COMMAND_FUNC_H

#include "command_type.h"
#include "company_type.h"

/**
 * Returns a specific StringID as error.
 *
 * @param error_msg The StringID to return
 */
inline CommandCost CommandError(StringID error_msg = INVALID_STRING_ID) { return CommandCost(error_msg); }

CommandCost DoCommand(TileIndex tile, uint32 p1, uint32 p2, DoCommandFlag flags, uint32 cmd, const char *text = nullptr);
CommandCost DoCommand(const CommandContainer *container, DoCommandFlag flags);

bool DoCommandP(TileIndex tile, uint32 p1, uint32 p2, uint32 cmd, CommandCallback *callback = nullptr, const char *text = nullptr, bool my_cmd = true, uint32 binary_length = 0);
bool DoCommandP(const CommandContainer *container, bool my_cmd = true);

CommandCost DoCommandPInternal(TileIndex tile, uint32 p1, uint32 p2, uint32 cmd, CommandCallback *callback, const char *text, bool my_cmd, bool estimate_only, uint32 binary_length);

#ifdef ENABLE_NETWORK
void NetworkSendCommand(TileIndex tile, uint32 p1, uint32 p2, uint32 cmd, CommandCallback *callback, const char *text, CompanyID company, uint32 binary_length);
#endif /* ENABLE_NETWORK */

extern Money _additional_cash_required;

bool IsValidCommand(uint32 cmd);
CommandFlags GetCommandFlags(uint32 cmd);
const char *GetCommandName(uint32 cmd);
Money GetAvailableMoneyForCommand();
bool IsCommandAllowedWhilePaused(uint32 cmd);

/**
 * Extracts the DC flags needed for DoCommand from the flags returned by GetCommandFlags
 * @param cmd_flags Flags from GetCommandFlags
 * @return flags for DoCommand
 */
static inline DoCommandFlag CommandFlagsToDCFlags(CommandFlags cmd_flags)
{
	DoCommandFlag flags = DC_NONE;
	if (cmd_flags & CMD_NO_WATER) flags |= DC_NO_WATER;
	if (cmd_flags & CMD_AUTO) flags |= DC_AUTO;
	if (cmd_flags & CMD_ALL_TILES) flags |= DC_ALL_TILES;
	return flags;
}

void ClearCommandLog();
char *DumpCommandLog(char *buffer, const char *last);

/*** All command callbacks that exist ***/

/* ai/ai_instance.cpp */
CommandCallback CcAI;

/* airport_gui.cpp */
CommandCallback CcBuildAirport;

/* bridge_gui.cpp */
CommandCallback CcBuildBridge;

/* dock_gui.cpp */
CommandCallback CcBuildDocks;
CommandCallback CcPlaySound_SPLAT_WATER;

/* depot_gui.cpp */
CommandCallback CcCloneVehicle;

/* game/game_instance.cpp */
CommandCallback CcGame;

/* group_gui.cpp */
CommandCallback CcCreateGroup;
CommandCallback CcAddVehicleNewGroup;

/* industry_gui.cpp */
CommandCallback CcBuildIndustry;

/* main_gui.cpp */
CommandCallback CcPlaySound_EXPLOSION;
CommandCallback CcPlaceSign;
CommandCallback CcTerraform;
CommandCallback CcGiveMoney;

/* plans_gui.cpp */
CommandCallback CcAddPlan;

/* rail_gui.cpp */
CommandCallback CcPlaySound_SPLAT_RAIL;
CommandCallback CcRailDepot;
CommandCallback CcStation;
CommandCallback CcBuildRailTunnel;

/* road_gui.cpp */
CommandCallback CcPlaySound_SPLAT_OTHER;
CommandCallback CcBuildRoadTunnel;
CommandCallback CcRoadDepot;
CommandCallback CcRoadStop;

/* train_gui.cpp */
CommandCallback CcBuildWagon;

/* town_gui.cpp */
CommandCallback CcFoundTown;
CommandCallback CcFoundRandomTown;

/* vehicle_gui.cpp */
CommandCallback CcBuildPrimaryVehicle;
CommandCallback CcStartStopVehicle;

/* tbtr_template_gui_create.cpp */
CommandCallback CcSetVirtualTrain;
CommandCallback CcVirtualTrainWagonsMoved;
CommandCallback CcDeleteVirtualTrain;

/* build_vehicle_gui.cpp */
CommandCallback CcAddVirtualEngine;


#endif /* COMMAND_FUNC_H */
