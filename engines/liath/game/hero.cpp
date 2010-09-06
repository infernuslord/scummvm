/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "liath/game/hero.h"

#include "liath/game/game.h"
#include "liath/game/expression.h"
#include "liath/game/work.h"

#include "liath/resource.h"
#include "liath/helpers.h"
#include "liath/liath.h"

namespace Liath {

HeroManager::HeroManager(LiathEngine *engine) : _engine(engine), _storage(NULL) {
	memset(&_heroParams, 0, sizeof(_heroParams));
}

HeroManager::~HeroManager() {
	// Zero-out passed pointers
	_engine = NULL;

	// Clear hero storage
	CLEAR_ARRAY(Hero, _heros);

	SAFE_FREE(_storage);
}

//////////////////////////////////////////////////////////////////////////
// Loading
//////////////////////////////////////////////////////////////////////////
void HeroManager::load(uint32 count, size_t varSize) {
	// Open hero data file
	Common::SeekableReadStream *stream = getResource()->createReadStreamForMember("game0001.dat");
	if (!stream)
		error("HeroManager::loadData: Invalid hero data stream!");

	// Go to the hero data
	stream->seek(stream->size() - 38 * count, SEEK_SET);

	// Setup hero data area
	for (uint32 i = 0; i <= count + 1; i++) {
		Hero *hero = new Hero();

		if (i > 0)
			stream->read(hero, 38);

		_heros.push_back(hero);
	}

	delete stream;

	// ALlocate storage for hero variables
	_storage = calloc((count + 1) * varSize, 1);

	// Setup hero objects
	for (uint i = 0; i < count + 1; ++i)
		get(i)->object = (HeroObject *)((byte *)_storage + i * varSize);
}

void HeroManager::unload() {
	for (uint index = 1; index < _heros.size(); index++)
		remove(index);
}

//////////////////////////////////////////////////////////////////////////
// Accessors
//////////////////////////////////////////////////////////////////////////

Hero *HeroManager::get(HeroIndex index) {
	if (index >= _heros.size())
		error("Hero::get: Invalid index (was:%d, max:%d)", index, _heros.size() - 1);

	return _heros[index];
}

//////////////////////////////////////////////////////////////////////////
// Opcodes
//////////////////////////////////////////////////////////////////////////
OpcodeRet HeroManager::start(OpcodeParameters *parameters, Work *work, void *unkown) {
	error("HeroManager::start: Not implemented!");
}

OpcodeRet HeroManager::startExt(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	switch (params->param5) {
	default:
		break;

	case kOriginGlobal:
		params->param2 = GLOBAL(params->param7);
		break;

	case kOriginHero:
		params->param2 = getData(params->param6, params->param7);
		break;

	case kOriginHeroWork:
		params->param2 = getData(getWork()->getCurrent()->heroIndex, params->param7);
		break;
	}

	switch (params->param8) {
	default:
		break;

	case kOriginGlobal:
		params->param1 = GLOBAL(params->param10);
		break;

	case kOriginHero:
		params->param1 = getData(params->param9, params->param10);
		break;

	case kOriginHeroWork:
		params->param1 = getData(getWork()->getCurrent()->heroIndex, params->param10);
		break;
	}

	return start((OpcodeParameters *)params, NULL, NULL);
}

OpcodeRet HeroManager::reset(OpcodeParameters *parameters, void *unkown) {
	error("HeroManager::reset: Not implemented!");
}

OpcodeRet HeroManager::exit(OpcodeParameters *parameters) {
	error("HeroManager::exit: Not implemented!");
}

OpcodeRet HeroManager::save(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	Work *work = getWork()->get(params->param1);

	if (work->field_C)
		return kOpcodeRetDefault;

	// Update hero params
	_heroParams.param1 = work->field_68;
	_heroParams.param2 = work->heroIndex;
	_heroParams.param3 = work->field_76;
	_heroParams.param10 = work->field_35;
	_heroParams.param12 = work->field_39;
	_heroParams.param14 = work->field_3D;
	_heroParams.param16 = work->field_41;
	_heroParams.param18 = work->field_45;
	_heroParams.param20 = work->field_34;
	_heroParams.param21 = 1;
	_heroParams.param22 = work->field_FA;

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::load() {
	if (getWork()->get(_heroParams.param2))
		reset(&_heroParams, NULL);
	else
		start(&_heroParams, NULL, NULL);

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::passVariable(OpcodeParameters *parameters) {
	error("HeroManager::passVariable: Not implemented!");
}

OpcodeRet HeroManager::freeze(OpcodeParameters *parameters) {
	error("HeroManager::freeze: Not implemented!");
}

OpcodeRet HeroManager::freezeGlobal(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = GLOBAL(params->param3);
	return freeze((OpcodeParameters *)params);
}

OpcodeRet HeroManager::freezeHeroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(params->param2, params->param3);
	return freeze((OpcodeParameters *)params);
}

OpcodeRet HeroManager::freezeVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(getWork()->getCurrent()->heroIndex, params->param3);
	return freeze((OpcodeParameters *)params);
}

OpcodeRet HeroManager::unfreeze(OpcodeParameters *parameters) {
	error("HeroManager::unfreeze: Not implemented!");
}

OpcodeRet HeroManager::unfreezeGlobal(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = GLOBAL(params->param3);
	return unfreeze((OpcodeParameters *)params);
}

OpcodeRet HeroManager::unfreezeHeroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(params->param2, params->param3);
	return unfreeze((OpcodeParameters *)params);
}

OpcodeRet HeroManager::unfreezeVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(getWork()->getCurrent()->heroIndex, params->param3);
	return unfreeze((OpcodeParameters *)params);
}

OpcodeRet HeroManager::herovar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	debugC(kLiathDebugInterpreter, "  heroIndex: %d / offset: %d  -  expression: %d - count: %d\n", params->param1, params->param2, params->param4, params->param3);

	setData(params->param1, params->param2, EXPR(params->param4, params->param3));

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::herovarGlobal(OpcodeParameters *parameters) {
	error("HeroManager::herovar_glb: Not implemented!");
}

OpcodeRet HeroManager::herovarHeroVar(OpcodeParameters *parameters) {
	error("HeroManager::herovar_hvar: Not implemented!");
}

OpcodeRet HeroManager::herovarVar(OpcodeParameters *parameters) {
	error("HeroManager::herovar_var: Not implemented!");
}

OpcodeRet HeroManager::heroSys(OpcodeParameters *parameters) {
	error("HeroManager::hero_sys: Not implemented!");
}

OpcodeRet HeroManager::var(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	setData(getWork()->getCurrent()->heroIndex, params->param1, EXPR(params->param3, params->param2));

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::sys(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	setData(getWork()->getCurrent()->heroIndex, params->param1, EXPR(params->param3, params->param2));

	switch (params->param1) {
	default:
		break;

	case 12:
		getWork()->getCurrent()->field_57 |= 1;
		break;

	case 13:
		getWork()->getCurrent()->field_57 |= 2;
		break;

	case 2:
		getWork()->getCurrent()->field_57 |= 4;
		break;

	case 14:
		getWork()->getCurrent()->field_57 |= 8;
		break;

	case 0:
		getWork()->getCurrent()->field_57 |= 16;
		break;

	case 1:
		getWork()->getCurrent()->field_57 |= 32;
		break;
	}

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::quitHero(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	return quit(params->param1);
}

OpcodeRet HeroManager::quitGlobal(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	return quit(GLOBAL(params->param3));
}

OpcodeRet HeroManager::quitHeroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	return quit(getData(params->param2, params->param3));
}

OpcodeRet HeroManager::quitVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	return quit(getData(getWork()->getCurrent()->heroIndex, params->param3));
}

OpcodeRet HeroManager::auto2hero(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	return RET(auto2((OpcodeParameters *)params) == kOpcodeRetNext, params->test);
}

OpcodeRet HeroManager::auto2heroGlobal(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = GLOBAL(params->param2);
	return auto2((OpcodeParameters *)params);
}

OpcodeRet HeroManager::auto2heroHeroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(params->param1, params->param2);
	return auto2((OpcodeParameters *)params);
}

OpcodeRet HeroManager::auto2heroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(getWork()->getCurrent()->heroIndex, params->param2);
	return auto2((OpcodeParameters *)params);
}

OpcodeRet HeroManager::face2hero(OpcodeParameters *parameters) {
	error("HeroManager::face2hero: Not implemented!");
}

OpcodeRet HeroManager::face2heroGlobal(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = GLOBAL(params->param2);

	if (face2hero((OpcodeParameters *)params) != -1)
		SETGLOBAL(params->param2, -1);

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::face2heroHeroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	uint32 param = params->param1;

	params->param1 = getData(params->param1, params->param2);

	if (face2hero((OpcodeParameters *)params) != -1)
		SETGLOBAL(params->param2, -1);

	params->param1 = param;

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::face2heroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	params->param1 = getData(getWork()->getCurrent()->heroIndex, params->param2);

	if (face2hero((OpcodeParameters *)params) != -1)
		SETGLOBAL(params->param2, -1);

	return kOpcodeRetDefault;
}

OpcodeRet HeroManager::hearGlobal(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	OpcodeRet ret = hear((OpcodeParameters *)params);

	SETGLOBAL(params->param2,  ret);

	if (ret != kOpcodeRetNext)
		ret = kOpcodeRetDefault;

	return (OpcodeRet)(params->test ? ret : -ret);
}

OpcodeRet HeroManager::hearHeroVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	OpcodeRet ret = hear((OpcodeParameters *)params);

	setData(params->param1, params->param2, ret);

	if (ret != kOpcodeRetNext)
		ret = kOpcodeRetDefault;

	return (OpcodeRet)(params->test ? ret : -ret);
}

OpcodeRet HeroManager::hearVar(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersDefault);

	OpcodeRet ret = hear((OpcodeParameters *)params);

	setData(getWork()->getCurrent()->heroIndex, params->param2, ret);

	if (ret != kOpcodeRetNext)
		ret = kOpcodeRetDefault;

	return (OpcodeRet)(params->test ? ret : -ret);
}

//////////////////////////////////////////////////////////////////////////
// Public functions
//////////////////////////////////////////////////////////////////////////

void HeroManager::remove(HeroIndex index) {
	error("HeroManager::remove: Not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////////

OpcodeRet HeroManager::quit(HeroIndex heroIndex) {
	error("HeroManager::quit: Not implemented!");
}

OpcodeRet HeroManager::auto2(OpcodeParameters *parameters) {
	error("HeroManager::auto2: Not implemented!");
}

OpcodeRet HeroManager::hear(OpcodeParameters *parameters) {
	error("HeroManager::auto2: Not implemented!");
}

} // End of namespace Liath
