/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>

#include "Audio.h"

Audio::Audio() : musiqueId(0), specialId(0) {
    SOUND = true;
    music = NULL;
    
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1) SOUND = false;
    
    if (SOUND) {
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
        previous_volume = Mix_VolumeMusic(32);
        loadSounds();
        setVolson(32);
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        Mix_PauseMusic();
        Mix_VolumeMusic(previous_volume);
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        Mix_CloseAudio();
    }
}

void Audio::setVolume(int volume) {
	Mix_VolumeMusic(volume);
}

void Audio::setVolson(int volson) {
    if (volson < 0 || volson > MIX_MAX_VOLUME) {
        fprintf(stderr, "Volume out of range. It must be between 0 and %d\n", MIX_MAX_VOLUME);
        return;
    }

    for (int i = 0; i < 40; i++) {
        if (!sons[i]) {
            fprintf(stderr, "Audio chunk at index %d is null. SDL Error: %s\n", i, SDL_GetError());
            continue;
        }
        Mix_VolumeChunk(sons[i], volson);
    }
}

void Audio::loadSounds() {
    sons = new Mix_Chunk*[40];

    sons[0] = Mix_LoadWAV("data/sound/text.wav"); // lettres
    sons[1] = Mix_LoadWAV("data/sound/menu1.wav"); // menu 1
    sons[2] = Mix_LoadWAV("data/sound/menu2.wav"); // menu 2
    sons[3] = Mix_LoadWAV("data/sound/menu3.wav"); // menu 3
    sons[4] = Mix_LoadWAV("data/sound/menu4.wav"); // menu 4
    sons[5] = Mix_LoadWAV("data/sound/timewarp.wav"); // time retour
    sons[6] = Mix_LoadWAV("data/sound/tombe.wav"); // tombe (ennemi)
    sons[7] = Mix_LoadWAV("data/sound/hitenemy.wav"); //shot 1
    sons[8] = Mix_LoadWAV("data/sound/killenemy.wav"); // shot 2
    sons[9] = Mix_LoadWAV("data/sound/surprise.wav"); // surprise
    sons[10] = Mix_LoadWAV("data/sound/monte.wav"); // monte
    sons[11] = Mix_LoadWAV("data/sound/descend.wav"); // descend
    sons[12] = Mix_LoadWAV("data/sound/chute.wav"); // chute
    sons[13] = Mix_LoadWAV("data/sound/item.wav"); // item
    sons[14] = Mix_LoadWAV("data/sound/rupee.wav"); // rubis
    sons[15] = Mix_LoadWAV("data/sound/heart.wav"); // coeur
    sons[16] = Mix_LoadWAV("data/sound/bomb.wav"); // bombe
    sons[17] = Mix_LoadWAV("data/sound/textnext.wav"); // suite texte
    sons[18] = Mix_LoadWAV("data/sound/textend.wav"); // fin texte
    sons[19] = Mix_LoadWAV("data/sound/happy.wav"); // trouve objet
    sons[20] = Mix_LoadWAV("data/sound/door.wav"); // ouvre porte
    sons[21] = Mix_LoadWAV("data/sound/pics.wav"); // pics contre mur
    sons[22] = Mix_LoadWAV("data/sound/sword.wav"); // Epée
    sons[23] = Mix_LoadWAV("data/sound/SwordCharging.wav"); // chargée
    sons[24] = Mix_LoadWAV("data/sound/Sword360.wav"); // spin
    sons[25] = Mix_LoadWAV("data/sound/shoot.wav"); // flèche
    sons[26] = Mix_LoadWAV("data/sound/hookshot.wav"); // grappin
    sons[27] = Mix_LoadWAV("data/sound/stamp.wav"); // pose bombe
    sons[28] = Mix_LoadWAV("data/sound/magic.wav"); // magie
    sons[29] = Mix_LoadWAV("data/sound/burn.wav"); // brËšle
    sons[30] = Mix_LoadWAV("data/sound/hammer.wav"); // marteau
    sons[31] = Mix_LoadWAV("data/sound/plouf.wav"); // plouf
    sons[32] = Mix_LoadWAV("data/sound/danger.wav"); // danger
    sons[33] = Mix_LoadWAV("data/sound/hurt.wav"); // link se blesse
    sons[34] = Mix_LoadWAV("data/sound/porte.wav"); // porte objet
    sons[35] = Mix_LoadWAV("data/sound/lance.wav"); // lance objet
    sons[36] = Mix_LoadWAV("data/sound/casse.wav"); // casse objet
    sons[37] = Mix_LoadWAV("data/sound/charge.wav"); // charge magie
    sons[38] = Mix_LoadWAV("data/sound/buisson.wav"); // coupe buisson
    sons[39] = Mix_LoadWAV("data/sound/pousse.wav"); // pousse caisse
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 40; i++) Mix_FreeChunk(sons[i]);
        delete[] sons;
    }
}

void Audio::playSound(int id, int chl) {
    if (SOUND) Mix_PlayChannel(chl,sons[id],0);
}

void Audio::playMusic(int id) {
    if (SOUND) {
        if (musiqueId != id) {
	    musiqueId = id;            
            if (specialId == 0) {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = choixMusique(id);
		Mix_PlayMusic(music,-1);
		specialId = 0;
	    }
        }
    }
}

void Audio::stopMusic() {
    if (SOUND) Mix_HaltMusic();
}

void Audio::replayMusic() {
    if (SOUND) Mix_PlayMusic(music,-1);
}

Mix_Music* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : return Mix_LoadMUS("data/music/Foret.mp3");
        case 2 : return Mix_LoadMUS("data/music/Plaine.mp3");
        case 3 : return Mix_LoadMUS("data/music/Lac.mp3");
        case 4 : return Mix_LoadMUS("data/music/Mont.mp3");
        case 5 : return Mix_LoadMUS("data/music/Desert.mp3");
        case 6 : return Mix_LoadMUS("data/music/Ombre.mp3");
        case 7 : return Mix_LoadMUS("data/music/Feu.mp3");
        case 8 : return Mix_LoadMUS("data/music/Cocorico.mp3");
        case 9 : return Mix_LoadMUS("data/music/Chateau.mp3");
        case 10 : case 11 : return Mix_LoadMUS("data/music/Secret.mp3");
        case 12 : case 13 : case 14 : return Mix_LoadMUS("data/music/Donjon1.mp3");
        case 15 : return Mix_LoadMUS("data/music/DDesert.mp3");
        case 16 : case 17 : case 18 : return Mix_LoadMUS("data/music/Donjon2.mp3");
        case 19 : return Mix_LoadMUS("data/music/DSecret.mp3");
        case 20 : return Mix_LoadMUS("data/music/DFinal.mp3");
        case 21 : return Mix_LoadMUS("data/music/Home.mp3");
        case 22 : case 23 : return Mix_LoadMUS("data/music/Cave.mp3");
        case 24 : case 25 : case 26 : case 27 : return Mix_LoadMUS("data/music/Fee.mp3"); break;
//case 28 : case 32 : case 35 : case 36 : case 38 : case 41 : case 42 : case 43 : case 44 :
//    return Mix_LoadMUS("data/music/Maison.mp3"); break;
        case 29 : case 37 : case 40 : return Mix_LoadMUS("data/music/Potion.mp3"); break;
        case 30 : return Mix_LoadMUS("data/music/Bar.mp3"); break;
        case 31 : return Mix_LoadMUS("data/music/Magasin.mp3"); break;
        case 33 : case 34 : case 39 : return Mix_LoadMUS("data/music/Jeu.mp3"); break;
        case 45 : return Mix_LoadMUS("data/music/Titre.mp3"); break;
        case 46 : return Mix_LoadMUS("data/music/Selection.mp3"); break;
        case 47 : return Mix_LoadMUS("data/music/Debut.mp3"); break;
        default : return Mix_LoadMUS("data/music/Maison.mp3");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
            Mix_HaltMusic();
            Mix_FreeMusic(music);
            music = choixSpecial(id);
            Mix_PlayMusic(music,-1);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

Mix_Music* Audio::choixSpecial(int id) {
    switch (id) {
        case 1 : return Mix_LoadMUS("data/music/Boss.mp3");
        case 2 : return Mix_LoadMUS("data/music/Mort.mp3");
        case 3 : return Mix_LoadMUS("data/music/Epee.mp3");
        case 4 : return Mix_LoadMUS("data/music/BossF.mp3");
        case 5 : return Mix_LoadMUS("data/music/Fin.mp3");
        default : return Mix_LoadMUS("data/music/Boss.mp3");
    }
}

