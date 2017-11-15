// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
uint8_t addr[16];
uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x67e3d3614287f7a7edb3696bab881554063f9e75d01ac0bddfc60da1e71c9808"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1502136266, // * UNIX timestamp of last checkpoint block
        0,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        750     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0xce7761c71a6a3c092dfc83dc2f523fc459f3f186f7ff4bfb3e51678ab0f2b738"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1510577755,
        0,
        250
    };

//static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
//        boost::assign::map_list_of
//        ( 0, uint256("0x3e7ddcebb5a01733d733a4671a791070e05669eaac79b0d8dae3116d13ed73a3"))
//        ;
//static const Checkpoints::CCheckpointData dataRegtest = {
//        &mapCheckpointsRegtest,
//        0,
//        0,
//        0
//    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0xca;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xeb;

        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 41184;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 840000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 4 * 60 * 60; // 10 minutes
        nTargetSpacing = 2.5 * 60; // 1 minute
        nMaxTipAge = 24 * 60 * 60;

        const char* pszTimestamp = "invictus genesis block";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1502136266;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 591108;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x67e3d3614287f7a7edb3696bab881554063f9e75d01ac0bddfc60da1e71c9808"));
        assert(genesis.hashMerkleRoot == uint256("0x9ec48a98eca7ff371ac7f5a4411d1d3077b700884333d4ee8a2bc07f97a7347c"));

        vSeeds.push_back(CDNSSeedData("cryptolife.net","wallet.cryptolife.net"));
        vSeeds.push_back(CDNSSeedData("cryptolife.net","explore.cryptolife.net"));
        vSeeds.push_back(CDNSSeedData("cryptolife.net","seed1.cryptolife.net"));
	vSeeds.push_back(CDNSSeedData("cryptolife.net","seed2.cryptolife.net"));
	vSeeds.push_back(CDNSSeedData("104.156.231.213","45.77.7.67"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,102);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,117);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        // Invictus: Mainnet v2 enforced as of block 710k
        nEnforceV2AfterHeight = 710000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xbc;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0xaf;
        pchMessageStart[3] = 0xc4;

        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 36005;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 10 * 60; // 10 minutes
        nTargetSpacing = 1 * 60; // 1 minute
        nMaxTipAge = 0x7fffffff;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1510577755;
        genesis.nNonce = 578468;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xce7761c71a6a3c092dfc83dc2f523fc459f3f186f7ff4bfb3e51678ab0f2b738"));

        vFixedSeeds.clear();
        vSeeds.clear();


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        // Invictus: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
//class CRegTestParams : public CTestNetParams {
//public:
//    CRegTestParams() {
//        networkID = CBaseChainParams::REGTEST;
//        strNetworkID = "regtest";
//        pchMessageStart[0] = 0xad;
//        pchMessageStart[1] = 0xb7;
//        pchMessageStart[2] = 0x31;
//        pchMessageStart[3] = 0xdf;
//
//        nSubsidyHalvingInterval = 150;
//        nEnforceBlockUpgradeMajority = 750;
//        nRejectBlockOutdatedMajority = 950;
//        nToCheckBlockUpgradeMajority = 1000;
//        nMinerThreads = 1;
//        nTargetTimespan = 10 * 60; // 10 minutes
//        nTargetSpacing = 1 * 60; // 1 minute
//        bnProofOfWorkLimit = ~uint256(0) >> 1;
//        nMaxTipAge = 24 * 60 * 60;
//        genesis.nTime = 1503262638;
//        genesis.nBits = 0x207fffff;
//        genesis.nNonce = 2;
//        hashGenesisBlock = genesis.GetHash();
//        nDefaultPort = 36007;
//        assert(hashGenesisBlock == uint256("0x3e7ddcebb5a01733d733a4671a791070e05669eaac79b0d8dae3116d13ed73a3"));
//
//        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
//        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.
//
//        fRequireRPCPassword = false;
//        fMiningRequiresPeers = false;
//        fAllowMinDifficultyBlocks = true;
//        fDefaultConsistencyChecks = true;
//        fRequireStandard = false;
//        fMineBlocksOnDemand = true;
//        fTestnetToBeDeprecatedFieldRPC = false;

        // Invictus: v2 enforced using Bitcoin's supermajority rule
//        nEnforceV2AfterHeight = -1;
//    }
//    const Checkpoints::CCheckpointData& Checkpoints() const 
//    {
//        return dataRegtest;
//    }
//};
//static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;

        // Invictus: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        //case CBaseChainParams::REGTEST:
        //    return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
