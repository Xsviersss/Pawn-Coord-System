/*
 *  sscanf 2.13.8
 *
 *  Version: MPL 1.1
 *
 *  The contents of this file are subject to the Mozilla Public License Version
 *  1.1 (the "License"); you may not use this file except in compliance with
 *  the License. You may obtain a copy of the License at
 *  http://www.mozilla.org/MPL/
 *
 *  Software distributed under the License is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 *  for the specific language governing rights and limitations under the
 *  License.
 *
 *  The Original Code is the sscanf 2.0 SA:MP plugin.
 *
 *  The Initial Developer of the Original Code is Alex "Y_Less" Cole.
 *  Portions created by the Initial Developer are Copyright (c) 2022
 *  the Initial Developer. All Rights Reserved.
 *
 *  Contributor(s):
 *
 *      Cheaterman
 *      DEntisT
 *      Emmet_
 *      karimcambridge
 *      kalacsparty
 *      Kirima
 *      leHeix
 *      maddinat0r
 *      Southclaws
 *      Y_Less
 *      ziggi
 *
 *  Special Thanks to:
 *
 *      SA:MP Team past, present, and future.
 *      maddinat0r, for hosting the repo for a very long time.
 *      Emmet_, for his efforts in maintaining it for almost a year.
 */

#if defined _INC_SSCANF
	#endinput
#endif
#define _INC_SSCANF

#if !defined _samp_included
	#error Please include <a_npc> or <a_samp> first.
#endif

/**
 * <library
 *   name="sscanf"
 *   summary="Extracts structured information from strings."
 *   license="Copyright (c) 2022 Alex &quot;Y_Less&quot; Cole.  Licensed under MPL 1.1"
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     This is the <em>sscanf</em> plugin, which provides the <c>sscanf</c>
 *     function to extract basic structured data from strings.  This is slightly
 *     different to regular expressions, but both have their place.  A regular
 *     expression gives you total control over the exact structure of data down
 *     to the character level; however, extracting structured data like numbers
 *     using it is tricky.  Conversely this gives slightly higher-level
 *     <em>specifiers</em> which can easily extract data types, at the expense
 *     of fine-grained control.  To convert a string in to two numbers would
 *     look like:
 *     
 *     <code>
 *         new num1, num2;                                                          <br />
 *         sscanf("45 100", "ii", num1, num2);
 *     </code>
 *     
 *     <c>ii</c> is the specifier string, which here means "integer integer";
 *     stating that the input string should be two whole numbers in a row (which
 *     is - <c>"45 100"</c>).  <c>num1</c> and <c>num2</c> are the destination
 *     variables to store the found numbers in (after conversion from strings).
 *     You can check if the conversion failed by looking for a non-naught return
 *     value:
 *     
 *     <code>
 *         new num1, num2;                                                          <br />
 *         if (sscanf("hello 100", "ii", num1, num2))                               <br />
 *         {                                                                        <br /><indent />
 *             printf("The input was not two numbers.");                            <br />
 *         }
 *     </code>
 *     
 *     This will fail because <c>"hello"</c> is not a whole number (or indeed
 *     any type of number at all).  For more information on using the function
 *     refer to the tutorials or the reference documentation in
 *     <a href="https://github.com/Y-Less/sscanf/blob/master/README.md">the
 *     attached readme</a>.
 *   </remarks>
 * </library>
 */

/// <p/>

#define SSCANF_STATIC__
#if defined __PawnBuild
	#if __PawnBuild == 11
		// `const static` support.
		#undef SSCANF_STATIC__
		#define SSCANF_STATIC__ static
	#endif
#else
	#if !defined SSCANF_NO_NICE_FEATURES
		#error sscanf utilises community compiler features.  Use `#define SSCANF_NO_NICE_FEATURES` to live without (if you can call that living) or better yet download it here: github.com/pawn-lang/compiler/releases
	#endif
#endif

/**
 * <library>sscanf</library>
 * <remarks>
 * Was sscanf built for an NPC mode or a normal mode?
 * </remarks>
 */
#if defined GetDistanceFromMeToPoint
	// NPC script.
	static stock SSCANF_NPC = 1;
	#define SSCANF_NPC (1)
	#pragma library sscanf
#else
	static stock SSCANF_NPC = 0;
	#define SSCANF_NPC (0)
#endif

/**
 * <library>sscanf</library>
 * <remarks>
 * The sscanf major version number.
 * </remarks>
 */
static stock SSCANF_VERSION_MAJOR =  2;
#define SSCANF_VERSION_MAJOR  2

/**
 * <library>sscanf</library>
 * <remarks>
 * The sscanf minor version number.
 * </remarks>
 */
static stock SSCANF_VERSION_MINOR = 13;
#define SSCANF_VERSION_MINOR 13

/**
 * <library>sscanf</library>
 * <remarks>
 * The sscanf build number.
 * </remarks>
 */
static stock SSCANF_VERSION_BUILD = 8;
#define SSCANF_VERSION_BUILD  8

/**
 * <library>sscanf</library>
 * <remarks>
 * The sscanf version as a string.  E.g. <c>"2.8.1"</c>.
 * </remarks>
 */
static stock SSCANF_VERSION_STRING[] = #SSCANF_VERSION_MAJOR "." #SSCANF_VERSION_MINOR "." #SSCANF_VERSION_BUILD;
#define SSCANF_VERSION_STRING #SSCANF_VERSION_MAJOR "." #SSCANF_VERSION_MINOR "." #SSCANF_VERSION_BUILD

/**
 * <library>sscanf</library>
 * <remarks>
 * Converts a version string to
 * <a href="https://en.wikipedia.org/wiki/Binary-coded_decimal">BCD</a>.  For example:
 *
 * <code>
 *   BCD(5.6.17);
 * </code>
 *
 * Returns:
 *
 * <code>
 *   0x050617
 * </code>
 *
 * Each section (between dots) is assigned a single byte and the last section is
 * always in the lowest byte.  This implies a maximum of four sections and two
 * digits per section.
 *
 * </remarks>
 */
forward BCD(number);

#define BCD(%0) (_:MORE_BCD:NO_MORE_BCD:%0.$0)
#define MORE_BCD:NO_MORE_BCD:%0.%1$%2) MORE_BCD:NO_MORE_BCD:%1$(%2) << 8 | DO_BCD(%0))
#define NO_MORE_BCD:$
#define DO_BCD(%0) _:(%0) / 10 << 4 | _:(%0) % 10

/**
 * <library>sscanf</library>
 * <remarks>
 * The sscanf version in BCD as a proper constant.  Example:
 *
 * <code>
 *         2.10.3  <br />
 *     => 02 10 03 <br />
 *     => 0x021003
 * </code>
 * </remarks>
 */
const SSCANF_VERSION = BCD(SSCANF_VERSION_MAJOR.SSCANF_VERSION_MINOR.SSCANF_VERSION_BUILD);

/**
 * <library>sscanf</library>
 * <remarks>
 * The sscanf version in BCD.  Example:
 *
 * <code>
 *         2.10.3  <br />
 *     => 02 10 03 <br />
 *     => 0x021003
 * </code>
 * </remarks>
 */
stock const SSCANF_VERSION_BCD = SSCANF_VERSION;

#define sscanf_%0\32; sscanf_
#define SSCANF:%0(%1) forward sscanf_%0(%1);public sscanf_%0(%1)
#define @kustom()%0(%1) forward sscanf_%0(%1);public sscanf_%0(%1)

// The check for `SSCANF_GetClosestString` ensures that this is the first
// compiler pass and thus the check for `sscanf` only finds earlier definitions
// not our later fake definition made purely for documentation purposes.
#if defined sscanf && !defined SSCANF_GetClosestString
	#error sscanf already defined, or used before inclusion.
#endif

/**
 * <library>sscanf</library>
 * <param name="file">The file in which this call is found.</param>
 * <param name="line">The line at which this call is found.</param>
 * <param name="data">The input string containing the data to parse out.</param>
 * <param name="format">The format description of what the input data should contain.</param>
 * <remarks>
 * The current true implementation of <c>sscanf</c> in the plugin.  This is
 * wrapped by macros to provide <c>sscanf</c> enhanced with filenames and line
 * numbers so that errors have more information.  The plugin also contains a
 * native function called <c>sscanf</c> which is only for backwards-
 * compatibility with older versions of this include.
 * </remarks>
 */
/* */ native SSCANF__(const file[], const line, const data[], const format[], {T_WEAPON, Float, _}:...);

/**
 * <library>sscanf</library>
 * <param name="file">The file in which this call is found.</param>
 * <param name="line">The line at which this call is found.</param>
 * <param name="data">The input string containing the data to parse out.</param>
 * <param name="format">The format description of what the input data should contain.</param>
 * <remarks>
 * An alternative name for <c>SSCANF__</c>, used by <c>extract</c> so that the
 * name can be used as a macro.
 * </remarks>
 */
/* */ native UNFORMAT__(const file[], const line, const data[], const format[], {T_WEAPON, Float, _}:...) = SSCANF__;

/**
 * <library>sscanf</library>
 * <param name="players">The maximum players on the server.</param>
 * <param name="invalid">The invalid player ID.</param>
 * <param name="len"><c>MAX_PLAYER_NAME</c>.</param>
 * <remarks>
 * Initialise the plugin with real server information.
 * </remarks>
 */
/* */ native SSCANF_Init(players, invalid, len);

/**
 * <library>sscanf</library>
 * <param name="playerid">The ID of the player.</param>
 * <param name="name">The name of the player.</param>
 * <param name="npc">Is this player an NPC?</param>
 * <remarks>
 * Called when a player joins to inform the plugin of the connection.
 * </remarks>
 */
/* */ native SSCANF_Join(playerid, const name[], bool:npc);

/**
 * <library>sscanf</library>
 * <param name="playerid">The ID of the player.</param>
 * <remarks>
 * Called when a player leaves to inform the plugin of the disconnection.
 * </remarks>
 */
/* */ native SSCANF_Leave(playerid);

/**
 * <library>sscanf</library>
 * <param name="playerid">The ID of the player.</param>
 * <remarks>
 * Checks if the plugin knows about a given player ID.  Used when modes restart
 * to re-add players.
 * </remarks>
 */
/* */ native bool:SSCANF_IsConnected(playerid);

/**
 * <library>sscanf</library>
 * <param name="string1">The first string to compare.</param>
 * <param name="string2">The second string to compare.</param>
 * <remarks>
 * Computes the <a href="https://en.wikipedia.org/wiki/Levenshtein_distance">
 * Levenshtein Distance</a> between two strings.  This is simlar to
 * <c>strcmp</c> in usage, but is slightly more "fuzzy".  Distances are used to
 * work out which string is the most similar to another one, though they may not
 * be identical.  Useful in <c>k</c> callback functions to determine if the
 * entered string is close to a possible string.
 * </remarks>
 */
native SSCANF_Levenshtein(const string1[], const string2[]);

/**
 * <library>sscanf</library>
 * <param name="string1">The first string to compare.</param>
 * <param name="string2">The second string to compare.</param>
 * <remarks>
 * This works out the similarity between two strings.  The Levenshtein distance
 * often produces results that seem weird to people, for example by that measure
 * <c>NRG</c> is closer to <c>TUG</c> than <c>NRG-500</c>.  Instead this
 * function compares all pairs of letters between the two strings to work out
 * what percentage of each string is in the other string, then multiplies the
 * results to get the final similarity.  This algorithm produces much more human
 * sane results, and can handle things like <c>ls police<c> matching
 * <c>Police Car (LSPD)</c>.  It ignores all punctuation and case as well.
 * </remarks>
 */
native Float:SSCANF_TextSimilarity(const string1[], const string2[]);

/**
 * <library>sscanf</library>
 * <param name="name">The sscanf option to look up.  For example <c>SSCANF_COLOUR_FORMS</c>.</param>
 * <remarks>
 * The old API used <c>SSCANF_Option</c> to both get and set parse options,
 * with an optional parameter for setting.  This was problematic if you wanted
 * to actually set an option to the default value - there was no way to
 * differentiate between getting an option and setting an option to the default
 * value.  Instead the new API has explicit <c>Get</c> and <c>Set</c> functions.
 * </remarks>
 */
native SSCANF_GetOption(const name[]) = SSCANF_Option;

/**
 * <library>sscanf</library>
 * <param name="name">The sscanf option to look up.  For example <c>MATCH_NAME_PARTIAL</c>.</param>
 * <remarks>
 * The old API used <c>SSCANF_Option</c> to both get and set parse options,
 * with an optional parameter for setting.  This was problematic if you wanted
 * to actually set an option to the default value - there was no way to
 * differentiate between getting an option and setting an option to the default
 * value.  Instead the new API uses true parameter counts to differentiate in
 * the legacy <c>SSCANF_Option</c> function, which are resolved through macros
 * to <c>Get__</c> and <c>Set__</c> functions.
 * </remarks>
 */
/* */ native SSCANF_GetOption__(const name[]) = SSCANF_Option;

/**
 * <library>sscanf</library>
 * <param name="name">The sscanf option to set.  For example <c>CELLMIN_ON_MATCHES</c>.</param>
 * <param name="value">The value to set the option to.</param>
 * <remarks>
 * The old API used <c>SSCANF_Option</c> to both get and set parse options,
 * with an optional parameter for setting.  This was problematic if you wanted
 * to actually set an option to the default value - there was no way to
 * differentiate between getting an option and setting an option to the default
 * value.  Instead the new API has explicit <c>Get</c> and <c>Set</c> functions.
 * </remarks>
 */
native SSCANF_SetOption(const name[], {_, Float}:value) = SSCANF_Option;

/**
 * <library>sscanf</library>
 * <param name="name">The sscanf option to set.  For example <c>OLD_DEFAULT_CUSTOM</c>.</param>
 * <param name="value">The value to set the option to.</param>
 * <remarks>
 * The old API used <c>SSCANF_Option</c> to both get and set parse options,
 * with an optional parameter for setting.  This was problematic if you wanted
 * to actually set an option to the default value - there was no way to
 * differentiate between getting an option and setting an option to the default
 * value.  Instead the new API uses true parameter counts to differentiate in
 * the legacy <c>SSCANF_Option</c> function, which are resolved through macros
 * to <c>Get__</c> and <c>Set__</c> functions.
 * </remarks>
 */
/* */ native SSCANF_SetOption__(const name[], {_, Float}:value) = SSCANF_Option;

/**
 * <library>sscanf</library>
 * <param name="name">The sscanf option to get or set.  For example <c>SSCANF_ARGB</c>.</param>
 * <param name="value">The optional value to use when setting the option.</param>
 * <remarks>
 * Backwards-compatibility with <c>SSCANF_Option</c>.  Usage:
 *
 * <code>
 *     SSCANF_Option(SSCANF_QUIET, 1);           <br />
 *     new quiet = SSCANF_Option(SSCANF_QUIET);
 * </code>
 *
 * This doesn't actually use a default parameter because a user may want to set
 * the option to whatever that parameter is.  Instead this is a macro that calls
 * <c>SSCANF_GetOption__</c> when called with one parameter (just a name), or
 * instead calls <c>SSCANF_SetOption__</c> when called with two - a name and a
 * value.
 * </remarks>
 */
forward SSCANF_Option(const name[], {_, Float}:value = -1);

#define SSCANF_Option SSCANF_GetOption__
#define SSCANF_GetOption__(%0,%1) SSCANF_SetOption__(%0,%1)
#define _ALS_SSCANF_Option
#define _ALS_SSCANF_GetOption__

/**
 * <library>sscanf</library>
 * <param name="version">Pass-by-reference return value.</param>
 * <param name="size">The size of the destination array.</param>
 * <remarks>
 * Get the SSCANF plugin version as a string (e.g. <c>"2.11.2"</c>).  Compare
 * this value to the constant <c>SSCANF_VERSION_STRING</c>.
 * </remarks>
 */
native SSCANF_VersionString(version[], size = sizeof (version)) = SSCANF_Version;

/**
 * <library>sscanf</library>
 * <param name="version">Pass-by-reference return value.</param>
 * <param name="size">The size of the destination array.</param>
 * <remarks>
 * Get the SSCANF plugin version as a string (e.g. <c>"2.11.2"</c>).  Compare
 * this value to the constant <c>SSCANF_VERSION_STRING</c>.  This internal
 * alternate spelling is used by the <c>SSCANF_Version</c> macro, which will
 * return a string when called with parameters, or a BCD value when not.
 * </remarks>
 */
/* */ native SSCANF_VersionString__(version[], size = sizeof (version)) = SSCANF_Version;

/**
 * <library>sscanf</library>
 * <remarks>
 * Get the SSCANF plugin version as a BCD-encoded value (e.g. <c>0x021102</c>).
 * Compare this value to the constant <c>SSCANF_VERSION_BCD</c>.
 * </remarks>
 */
native SSCANF_VersionBCD() = SSCANF_Version;

/**
 * <library>sscanf</library>
 * <remarks>
 * Get the SSCANF plugin version as a BCD-encoded value (e.g. <c>0x021102</c>).
 * Compare this value to the constant <c>SSCANF_VERSION_BCD</c>.  This internal
 * alternate spelling is used by the <c>SSCANF_Version</c> macro, which will
 * return a string when called with parameters, or a BCD value when not.
 * </remarks>
 */
/* */ native SSCANF_VersionBCD__() = SSCANF_Version;

// The `SSCANF_Version` function is overloaded to take 0 or 2 parameters (or 1 plus a default).

/**
 * <library>sscanf</library>
 * <param name="version">Pass-by-reference return value.</param>
 * <param name="size">The size of the destination array.</param>
 * <remarks>
 * Get the SSCANF plugin version as a string (e.g. <c>"2.11.2"</c>) <em>or</em>
 * a BCD-encoded value (e.g. <c>0x021102</c>).  This function returns a string
 * (by reference) when called with parameters, or a number (directly) when not.
 * </remarks>
 */
static stock SSCANF_Version(version[] = "", size = sizeof (version))
{
	return SSCANF_VERSION_BCD;
}

#define SSCANF_Version SSCANF_VersionString__
#define SSCANF_VersionString__() SSCANF_VersionBCD__()
#define _ALS_SSCANF_Version
#define _ALS_SSCANF_VersionString__

/**
 * <library>sscanf</library>
 * <param name="data">The input string containing the data to parse out.</param>
 * <param name="format">The format description of what the input data should contain.</param>
 * <remarks>
 * The main entry point.  See the readme for vast amounts of information on how
 * to call this function and all the details on what it does.  This is a macro
 * that calls <c>SSCANF__</c> and passes the current file and line number as
 * well for improved error messages.
 * </remarks>
 */

#if defined __PawnBuild
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated - include <sscanf2> first.
forward sscanf(const data[], const format[], {T_WEAPON, Float, _}:...);

#if defined __PawnBuild
	#pragma warning pop
#endif

// For pawno native detection.
/*
native sscanf(const data[], const format[], {T_WEAPON, Float, _}:...);
*/

#if defined __PawnBuild
	#define sscanf( SSCANF__(__file,__line,
#else
	// `-1` because the old compiler doesn't have `__line` so we can't know
	// where this function was used.  Tell the plugin this.  Actually, we *can*
	// know, if we look at the CIP and try extract the file/line information
	// from any included debug information.  `SSCANF_UNK_` tells the plugin that
	// this was called via `sscanf` not `unformat`, because they're actually the
	// same function once compiled.
	#define sscanf( SSCANF__(SSCANF_UNK_,-1,
#endif

/**
 * - include <sscanf2> first.
 * <library>sscanf</library>
 * <param name="data">The input string containing the data to parse out.</param>
 * <param name="format">The format description of what the input data should contain.</param>
 * <remarks>
 * An alternative spelling of <c>sscanf</c>, requested by Kalcor because the
 * original doesn't match the C specification for the format descriptor.  This
 * is a macro that calls <c>UNFORMAT__</c> and passes the current file and line
 * number as well for improved error messages.
 * </remarks>
 */

#if defined __PawnBuild
	// On old compilers, only issue the warning at the call site.
	#pragma warning push
	#pragma warning disable 234
#endif

#pragma deprecated -