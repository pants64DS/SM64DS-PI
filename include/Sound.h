#pragma once

#include "Math.h"

struct ROM_Info;
struct Actor;

namespace Sound
{
	enum RecordType
	{
		RC_SEQUENCE,
		RC_SEQUENCE_ARCHIVE,
		RC_INSTRUMENT_BANK,
		RC_WAVE_ARCHIVE,
		RC_PLAYER, //???
		RC_GROUP,
		RC_PLAYER2, //???
		RC_STREAM //D.N.E. (Does Not Exist) for SM64DS
	};

	struct SDAT_Header
	{
		struct Block
		{
			u32 offset;
			u32 size;
		};
		char magic[4]; //"SDAT"
		u32 x0100feff;
		u32 fileSize;
		u16 headerSize;
		u16 numBlocks;
		Block symbolBlock;
		Block infoBlock;
		Block fat;
		Block fileBlock;		
	};

	struct SymbolBlock
	{

	};

	struct InfoSequenceEntry
	{
		u32 fileID;
		u16 bank;
		u8 volume;
		u8 channelPressure; //???
		u8 polyphonicPressure; //???
		u8 play; //???
		u16 padding;

		static InfoSequenceEntry* GetWithID(u32 seqID);
	};

	struct InfoInstrumentBankEntry
	{
		u32 fileID;
		u16 waveArchiveIDs[4];

		static InfoInstrumentBankEntry* GetWithID(u32 bankID);
	};

	struct InfoBlockRecord
	{
		u32 count;
		u32 entryOffsets[]; //size = count
	};

	struct InfoBlock
	{
		char magic[4]; //"INFO"
		u32 size;
		u32 recordOffsets[8];
		char padding[0x18];
	};

	struct FAT
	{

	};

	struct FileBlock
	{

	};

	struct Sequence
	{

	};

	struct InstrumentBank
	{

	};

	struct WaveArchive
	{
		char magic[4]; //"SWAR"
		u32 x0100feff;
		u32 fileSize;
		u16 headerSize;
		u16 one;
	};

	struct SDAT_RAM
	{
		SDAT_Header header;
		u32 unk30;
		u32 unk34;
		ROM_Info* rom;
		u32 unk3c;
		u32 unk40;
		u32 unk44;
		u32 unk48;
		u32 unk4c;
		u32 unk50;
		u32 unk54;
		u32 unk58;
		WaveArchive* waveArchive;
		u32 waveArchiveSize;
		u32 unk64; //waveArchiveSize copy?
		u32 unk68;
		u32 unk6c;
		u32 unk70;
		u32 unk74; //ROM?
		u32 unk78;
		FAT* fileAllocTable;
		u32 unk80;
		InfoBlock* infoBlock;

		static SDAT_RAM* PTR;
	};

	struct SequenceArchive
	{
		struct Data
		{
			struct SampleDef
			{
				u32 unk0;
				u16 bankID;
				u8 volume;
				u8 unk7;
				u8 unk8;
				u8 unk9;
				u8 unka;
				u8 unkb;
			};

			char magic[4]; //"DATA"
			u32 size;
			u32 sampleDefSize;
			u32 numSamples;
			SampleDef sampleDefs[];
		};

		char magic[4]; //"SSAR"
		u16 endianCode; //0xfeff
		u16 unk6;
		u32 size; //includes header
		u32 dataOffset; //0x10
		u32 unke;
		Data data;
	};

	struct Player; // needs to be declared here because otherwise FileRef::soundPlayer would be a ::Player*

	struct FileRef //guess
	{
		FileRef** unk0;
		Player* soundPlayer;
		char* file;
		u32 unk0c;
		u32 unk10;
		u32 unk14;
		u32 unk18;
		u32 unk1c;
		u32 unk20;
		u32 unk24;
		u32 unk28;
		u32 unk2c;
		u32 unk30;
		u32 unk34;
		u32 unk38;
		u8 unk3c;
		u8 unk3d;
		u8 unk3e;
		u8 unk3f;

		static FileRef* MUSIC_PTR;
		static FileRef* SOUND_PTR;
	};

	struct Player //not to be confused with ::Player
	{
		FileRef* fileRef;
		FileRef* fileRefCopy;
		u16 unk08;
		u16 unk0a;
		char* unk0c;
		char* unk10;
		u32 unk14;
		u32 unk18;

		static void SetPlayableSeqCount(s32 playerID, s32 maxSequences);
	};

	extern Player PLAYERS[]; //size not known, but greater than 9.

	u32 PlaySoundEmitter(u32 uniqueID, u32 archiveID, u32 soundID, const Vector3& pos, u16 fadeFrames = 0);
	u32 PlaySoundEmitter(u32 uniqueID, u32 archiveID, u32 soundID, u16 fadeFrames = 0);

	u32 PlaySoundEmitter3D(u32 uniqueID, u32 archiveID, u32 soundID, const Vector3& pos, Fix12i speed, u16 fadeFrames = 0);
	u32 PlaySoundEmitter3D(u32 uniqueID, u32 archiveID, u32 soundID, u32 arg3, s32 pitch, const Vector3& pos, u16 fadeFrames = 0);
	
	u32 PlayVoiceSeEmitter3D(u32 soundEmitterID, u8 characterID, u32 soundID, const Vector3& pos, u16 fadeFrames = 0);

	[[gnu::always_inline]]
	u32 PlayLong(u32 uniqueID, u32 archiveID, u32 soundID, const Vector3& pos, u16 fadeFrames = 0)
	{
		return PlaySoundEmitter(uniqueID, archiveID, soundID, pos, fadeFrames); 
	}

	void Play(u32 archiveID, u32 soundID, const Vector3& camSpacePos);
	void PlayMovingDoppler(u32 archiveID, u32 soundID, const Vector3& camSpacePos, Fix12i speed);
	u32 Play2D(u32 archiveID, u32 soundID);


	// Hb: a lot of the following are implemented quite similarly, as such the "duplicates" will be suffixed with "_" followed by their general usage

	// arc 0
	void PlayPlayerSe(u32 soundID, const Vector3& camSpacePos); // deprecated, use Sound::Play

	// arc 1
	void PlayVoiceSe(u8 characterID, u32 soundID); // deprecated, use Sound::Play2D
	void PlayVoiceSe(u8 characterID, u32 soundID, const Vector3& pos); // deprecated, use Sound::Play

	// arc 2
	void PlaySystemSe(u32 soundID); // deprecated, use Sound::Play2D
	void PlaySystemSe_Mg(u32 soundID); // deprecated, use Sound::Play2D
	void PlaySystemSe_Mg(u32 soundID, s32 pan); // deprecated, use Sound::Play2D
	
	// arc 3
	void PlaySceneSe(u32 soundID); // deprecated, use Sound::Play2D
	void PlaySceneSe(u32 soundID, const Vector3& camSpacePos); // deprecated, use Sound::Play
	void PlaySceneSe_1up(u32 soundID); // deprecated, use Sound::Play2D
	void PlaySceneSe_Boss(u32 soundID, const Vector3& camSpacePos); // deprecated, use Sound::Play
	void PlaySceneSe_Specific(u32 soundID, const Vector3& camSpacePos); // deprecated, use Sound::Play


	void LoadGroupAndSetBank(s32 groupID, s32 bankID);
	void LoadInitialGroup(s32 groupID);
	void UnsetPlayerVoiceGroup(); // only sets a variable to 0
	void ResetPlayerVoiceGroup(); // actually unloads the group

	void StartMusic(s32 musicID);
	void StopMusic(u32 fade);

	void PauseMusic();
	void UnpauseMusic();

	// volume goes up to 0x7f
	bool PlaySubMusic(u32 musicID, u32 musicTargetVolume, u32 subMusicTargetVolume, Fix12i maxStep, bool starting); // return value: did it finish?

	void StartBattleMusic(u32 musicID);
	void StopBattleMusic();

	void StartCharacterMusic(u32 playerID, u32 musicID); // will not start if battle music is already playing
	void StopCharacterMusic(u32 playerID, u32 musicID);

	void StartRaceMusic(u32 musicID);
	void StopRaceMusic();

	bool FadeMusic(u32 targetVolume, Fix12i maxStep);

	// Hb: these actually belong to Actor::
	bool PlaySmallSecretSound(Actor* actor, u16* timer); // returns whether finished playing sound
	bool PlaySecretSound(Actor* actor, u16* timer); // returns whether finished playing sound

	// Hb: we should move the following to a "Sound3D" namespace or whatever we end up calling it, they don't belong to the Sound:: namespace
	s32 GetPitch(u32 soundID, s32 pitch, const Vector3& pos, fx32 speed); // direct return
	void SetSoundDistancesDefault();
	void SetSoundDistancesChiefChilly();
	void SetSoundDistancesGoomboss();
}

extern s32 MUSIC_ID_LSL_12;
extern s32 MUSIC_VOLUME_LSL_12;
extern s32 MESSAGE_SOUND_VOLUME_LSL_12;
extern s32 SUB_MUSIC_ID;
extern s32 JRB_SOUND_SPECIFICS; // copied to SOUND_SPECIFICS if (JRB_SOUND_SPECIFICS > 0 && JRB_SOUND_SPECIFICS != SOUND_SPECIFICS)
extern s32 SOUND_SPECIFICS;