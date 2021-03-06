/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @author Christian <c@ethdev.com>
 * @date 2015
 * Versioning.
 */

#include <libsolidity/interface/Version.h>
#include <string>
#include <libdevcore/CommonData.h>
#include <libdevcore/Common.h>
#include <libsolidity/interface/Exceptions.h>
#include <lity/BuildInfo.h>

using namespace dev;
using namespace dev::solidity;
using namespace std;

char const* dev::solidity::SolcVersionNumber = ETH_PROJECT_VERSION;
char const* dev::solidity::LityVersionNumber = LITY_PROJECT_VERSION;

string const dev::solidity::SolcVersionString =
	string(dev::solidity::SolcVersionNumber) +
	(string(SOL_VERSION_PRERELEASE).empty() ? "" : "-" + string(SOL_VERSION_PRERELEASE)) +
	(string(SOL_VERSION_BUILDINFO).empty() ? "" : "+" + string(SOL_VERSION_BUILDINFO));

string const dev::solidity::SolcVersionStringStrict =
	string(dev::solidity::SolcVersionNumber) +
	(string(SOL_VERSION_PRERELEASE).empty() ? "" : "-" + string(SOL_VERSION_PRERELEASE)) +
	(string(SOL_VERSION_COMMIT).empty() ? "" : "+" + string(SOL_VERSION_COMMIT));

string const dev::solidity::LityVersionString =
	string(dev::solidity::LityVersionNumber) +
	(string(SOL_VERSION_PRERELEASE).empty() ? "" : "-" + string(SOL_VERSION_PRERELEASE)) +
	(string(SOL_VERSION_BUILDINFO).empty() ? "" : "+" + string(SOL_VERSION_BUILDINFO));

string const dev::solidity::LityVersionStringStrict =
	string(dev::solidity::LityVersionNumber) +
	(string(SOL_VERSION_PRERELEASE).empty() ? "" : "-" + string(SOL_VERSION_PRERELEASE)) +
	(string(SOL_VERSION_COMMIT).empty() ? "" : "+" + string(SOL_VERSION_COMMIT));

bytes dev::solidity::solcBinaryVersion()
{
	return binaryVersion(SolcVersionString);
}

bytes dev::solidity::lityBinaryVersion()
{
	return binaryVersion(LityVersionString);
}

bytes dev::solidity::binaryVersion(const std::string& versionString)
{
	bytes ret{0};
	size_t i = 0;
	auto parseDecimal = [&]()
	{
		size_t ret = 0;
		solAssert('0' <= versionString[i] && versionString[i] <= '9', "");
		for (; i < versionString.size() && '0' <= versionString[i] && versionString[i] <= '9'; ++i)
			ret = ret * 10 + (versionString[i] - '0');
		return ret;
	};
	ret.push_back(uint8_t(parseDecimal()));
	solAssert(i < versionString.size() && versionString[i] == '.', "");
	++i;
	ret.push_back(uint8_t(parseDecimal()));
	solAssert(i < versionString.size() && versionString[i] == '.', "");
	++i;
	ret.push_back(uint8_t(parseDecimal()));
	solAssert(i < versionString.size() && (versionString[i] == '-' || versionString[i] == '+'), "");
	++i;
	size_t commitpos = versionString.find("commit.");
	solAssert(commitpos != string::npos, "");
	i = commitpos + 7;
	solAssert(i + 7 < versionString.size(), "");
	bytes commitHash = fromHex(versionString.substr(i, 8));
	solAssert(!commitHash.empty(), "");
	ret += commitHash;
	solAssert(ret.size() == 1 + 3 + 4, "");

	return ret;
}

