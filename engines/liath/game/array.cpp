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

#include "liath/game/array.h"

#include "liath/game/expression.h"
#include "liath/game/game.h"

#include "liath/helpers.h"
#include "liath/liath.h"

#include "common/rational.h"

namespace Liath {

/**
 * Constructor.
 *
 * @param engine The engine instance.
 */
ArrayManager::ArrayManager(LiathEngine *engine) : _engine(engine) {
	memset(&_data, 0, sizeof(Array) * 10);
}

/**
 * Destructor.
 */
ArrayManager::~ArrayManager() {
	// Zero-out passed pointers
	_engine = NULL;
}

/**
 * Gets the array entry and check for the presence of data
 */
#define GET_ARRAY_ENTRY() \
	int32 index = getGame()->getValue((ParamOrigin)params->param1, params->param2, params->param3) - 1; \
	debugC(kLiathDebugInterpreter, "  index: %d - value(origin: %d, heroIndex: %d, offset: %d)\n", index, params->param1, params->param2, params->param3); \
	if (index < 0 || index >= 10) \
		return kOpcodeRetNext; \
	Array *array = &_data[index]; \
	if (!array->data || array->field_0 != index + 1) \
		return kOpcodeRetNext;

//////////////////////////////////////////////////////////////////////////
// Opcodes
//////////////////////////////////////////////////////////////////////////
OpcodeRet ArrayManager::init(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDD);

	Array *array = getFirstEmptyArray();
	if (!array)
		return kOpcodeRetDefault;

	getGame()->letValue((ParamOrigin)params->param1, params->param2, params->param3, array->field_0);

	// Allocate array data
	uint32 count = DSI2INT(EXPR(params->param16, params->param17));
	array->data = (ArrayData *)calloc(28 * count, 1);
	memset(array->data, 0, 28 * count);

	debugC(kLiathDebugInterpreter, "  value(origin: %d, heroIndex: %d, offset: %d, value: %d)", params->param1, params->param2, params->param3, array->field_0);
	debugC(kLiathDebugInterpreter, "  dataCount: %d (expression: %d - count: %d)\n", count, params->param16, params->param17);

	if (!array->data)
		return kOpcodeRetNext;

	// Update array entries
	array->dataCount = count;
	array->field_22 = 0;

	array->field_2[0] = DSI2INT(EXPR(params->param4,  params->param5));
	array->field_2[1] = DSI2INT(EXPR(params->param6,  params->param7));
	array->field_2[2] = DSI2INT(EXPR(params->param8,  params->param9));
	array->field_2[3] = DSI2INT(EXPR(params->param10, params->param11));
	array->field_2[4] = DSI2INT(EXPR(params->param12, params->param13));
	array->field_2[5] = DSI2INT(EXPR(params->param14, params->param15));

	array->field_1A = params->param18;

	array->setData(42, DSI2INT(EXPR(params->param19, params->param20)));
	array->setData(46, DSI2INT(EXPR(params->param21, params->param22)));
	array->setData(50, DSI2INT(EXPR(params->param23, params->param24)));
	array->setData(54, DSI2INT(EXPR(params->param25, params->param26)));

	array->field_3A = (array->getData(42) != array->getData(50)) ? 1 : 0;

	return kOpcodeRetDefault;
}

OpcodeRet ArrayManager::img(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDD2);

	GET_ARRAY_ENTRY();

	// Update array data
	array->field_56 = params->param9;

	array->setData(31, DSI2INT(EXPR(params->param11, params->param12)));
	array->setData(32, DSI2INT(EXPR(params->param13, params->param14)));
	array->setData(33, DSI2INT(EXPR(params->param15, params->param16)));
	array->setData(34, DSI2INT(EXPR(params->param17, params->param18)));
	array->setData(35, DSI2INT(EXPR(params->param19, params->param20)));
	array->setData(36, DSI2INT(EXPR(params->param21, params->param22)));

	int32 diff = array->field_2[2] - array->field_2[0] + 1;

	Common::Rational rat(diff, array->field_2[4]);
	rat.invert();
	rat *= array->dataCount;

	int32 count = ceil(rat.toDouble());
	int32 val = array->getData(34) - array->getData(32) +  array->field_2[5] * count + array->getData(36) * (count - 1) + 1;

	array->field_5A = diff;
	array->field_5E = val;

	// Allocate image data
	array->imgSize = 2 * val * diff;
	array->imgData = (uint32*)calloc(array->imgSize, 1);
	memset(array->imgData, 0, array->imgSize);

	return kOpcodeRetDefault;
}

OpcodeRet ArrayManager::add(OpcodeParameters *parameters) {
	error("ArrayManager::add: Not implemented!");
}


OpcodeRet ArrayManager::getNumber(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDB);

	GET_ARRAY_ENTRY();

	int32 val = getGame()->getValue((ParamOrigin)params->param4, params->param5, params->param6);

	if (!val)
		return kOpcodeRetNext;

	// Get index
	uint32 dataIndex;
	for (dataIndex = 0; (dataIndex < array->field_22 && array->data[dataIndex].field_0 != (uint32)val); ++dataIndex);

	if (dataIndex >= array->field_22)
		return kOpcodeRetNext;

	getGame()->letValue((ParamOrigin)params->param7, params->param8, params->param9, INT2DSI(dataIndex + 1));

	return kOpcodeRetDefault;
}

OpcodeRet ArrayManager::del(OpcodeParameters *parameters) {
	error("ArrayManager::del: Not implemented!");
}

OpcodeRet ArrayManager::kill(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDB);

	GET_ARRAY_ENTRY();

	if (array->field_22 >= array->dataCount)
		return kOpcodeRetNext;

	// Free data & clear content
	free(array->data);

	memset(array, 0, sizeof(Array));

	return kOpcodeRetDefault;
}

OpcodeRet ArrayManager::clear(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDB);

	GET_ARRAY_ENTRY();

	if (array->field_22 >= array->dataCount)
		return kOpcodeRetNext;

	// Clear data
	memset(array->data, 0, sizeof(ArrayData) * array->dataCount);

	return kOpcodeRetDefault;
}

OpcodeRet ArrayManager::get(OpcodeParameters *parameters) {
	error("ArrayManager::get: Not implemented!");
}

OpcodeRet ArrayManager::getScroll(OpcodeParameters *parameters) {
	error("ArrayManager::getScroll: Not implemented!");
}

OpcodeRet ArrayManager::size(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDB);

	GET_ARRAY_ENTRY();

	if (array->field_22 >= array->dataCount)
		return kOpcodeRetNext;

	getGame()->letValue((ParamOrigin)params->param4, params->param5, params->param6, INT2DSI(array->field_22));

	return kOpcodeRetDefault;
}

OpcodeRet ArrayManager::tget(OpcodeParameters *parameters) {
	error("ArrayManager::tget: Not implemented!");
}

OpcodeRet ArrayManager::cur(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDB);

	GET_ARRAY_ENTRY();



	if (array->field_22 >= array->dataCount)
		return kOpcodeRetNext;

	if (getGame()->getValue((ParamOrigin)params->param4, params->param5, params->param6) == (int32)array->data[array->dataCursor].field_0)
		return RET(1, params->test);
	else
		return RET(0, params->test);
}

OpcodeRet ArrayManager::setCur(OpcodeParameters *parameters) {
	EXPOSE_PARAMS(OpcodeParametersBDDD);

	GET_ARRAY_ENTRY();

	if (array->field_22 >= array->dataCount)
		return kOpcodeRetNext;

	int32 val = DSI2INT(EXPR(params->param4, params->param5));

	if (val >= (int32)(array->field_22 + 1))
		return kOpcodeRetNext;

	array->dataCursor = val - 1;

	return kOpcodeRetDefault;
}

//////////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////////
Array *ArrayManager::getFirstEmptyArray() {
	for (int i = 0; i < 10; i++) {

		if (_data[i].data)
			continue;

		_data[i+1].field_0 = i + 1;

		return &_data[i];
	}

	return NULL;
}

} // End of namespace Liath
