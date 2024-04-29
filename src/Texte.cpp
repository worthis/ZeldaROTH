/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "UTF8Utils.h"

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Texte::Texte(Jeu *jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
                         id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("")
{
    lastAnimTime = SDL_GetTicks();
    imageFont = IMG_Load("data/images/texte/font.png");
    SDL_SetColorKey(imageFont, SDL_SRCCOLORKEY, SDL_MapRGB(imageFont->format, 0, 0, 255));
    imageCoeur = IMG_Load("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur, SDL_SRCCOLORKEY, SDL_MapRGB(imageCoeur->format, 0, 0, 255));

    fontSize = 15;
    charWidth = 7;
    fontName = "data/images/texte/font.ttf";
    textColorFG = {248, 248, 248};
    textColorBG = {0, 0, 112};

    textFontFG = TTF_OpenFont(fontName.c_str(), fontSize);
    TTF_SetFontKerning(textFontFG, 0);
    TTF_SetFontHinting(textFontFG, TTF_HINTING_MONO);
    TTF_SetFontStyle(textFontFG, TTF_STYLE_NORMAL);
    textFontBG = TTF_OpenFont(fontName.c_str(), fontSize);
    TTF_SetFontKerning(textFontBG, 0);
    TTF_SetFontHinting(textFontBG, TTF_HINTING_MONO);
    TTF_SetFontStyle(textFontBG, TTF_STYLE_NORMAL);
    TTF_SetFontOutline(textFontBG, 1);
}

Texte::~Texte()
{
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);

    TTF_CloseFont(textFontFG);
    TTF_CloseFont(textFontBG);
}

void Texte::chercheText()
{
    ostringstream os;
    int tmp;
    switch (id)
    {
    case 1:
        texte = "Ты нашел щит!!!**Твоя защита увеличилась на одно очко!";
        break;
    case 2:
        texte = "Ты нашел меч!!!**Теперь ты можешь сражаться с монстрами нажатием кнопки A!!!*Удерживай кнопку A, чтобы зарядить круговой удар!!!";
        break;
    case 3:
        tmp = 4 - (gpJeu->getJoueur()->nbQuarts() % 4);
        os << tmp;
        texte = "Ты нашел частицу сердца!!!";
        if (tmp == 1)
        {
            buffer = "Найди еще одну частицу, чтобы получить дополнительное сердце!!!";
        }
        else if (tmp < 4)
        {
            buffer = "Найди еще " + os.str() + " частицы, чтобы получить дополнительное сердце!!!";
        }
        else
        {
            buffer = "Твое количество сердец увеличилось!!!";
        }
        break;
    case 11:
        texte = "С: Дом Линка*З: Поля Хайрула*В: Лесной Храм";
        break;
    case 12:
        texte = "Горный Храм**Не для слабонервных, трусливых и вообще малодушных.";
        break;
    case 13:
        texte = "З: Выход в Пустыню*С: Горный Храм";
        break;
    case 14:
        texte = "С: Горный Храм*Ю: Поля Хайрула";
        break;
    case 15:
        texte = "С: Гора Смерти";
        break;
    case 16:
        texte = "В: Проход в Лес";
        break;
    case 17:
        texte = "Ю: Озеро Хайлия*В: Кладбище с привидениями";
        break;
    case 18:
        texte = "Ю: Какарико";
        break;
    case 19:
        texte = "С: Какарико";
        break;
    case 20:
        texte = "С: Поля Хайрула";
        break;
    case 21:
        texte = "З: Огненные Земли";
        break;
    case 22:
        texte = "В: Деревня Теней*- Не для живых -";
        break;
    case 23:
        texte = "Темный Храм**Если ты призрак, ищущий работу, то тебе стоит зайти сюда и потусить с нами.";
        break;
    case 24:
        texte = "С: Деревня Теней*З: Озеро Хайлия";
        break;
    case 25:
        texte = "С: Кладбище с привидениями**Входа нет";
        break;
    case 26:
        texte = "Деревня Теней";
        break;
    case 27:
        texte = "Я продаю пустую бутылку за 100 рупий, не интересует?**          ? ДА ?           нет  ";
        if ((gpJeu->getJoueur()->hasBouteille(0) && gpJeu->getZone() == 8) ||
            (gpJeu->getJoueur()->hasBouteille(1) && gpJeu->getZone() == 5) ||
            (gpJeu->getJoueur()->hasBouteille(2) && gpJeu->getZone() == 6))
        {
            id = 32;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 100)
            idsuiv = 29;
        else
            idsuiv = 30;
        break;
    case 28:
        texte = "Я продаю пустую бутылку за 100 рупий, не интересует?**            да           ? НЕТ ?";
        idsuiv = 31;
        break;
    case 29:
        texte = "Приношу свои извинения, но у вас нехватает рупий для покупки.";
        break;
    case 30:
        texte = "Благодарю, вот ваша бутылка.";
        break;
    case 31:
        texte = "Возвращайтесь, если передумаете на счет покупки.";
        break;
    case 32:
        texte = "Прошу прощения, но это была последняя бутылка.";
        break;
    case 33:
        texte = "Ты получил пустую бутылку!!!**Она поможет тебе носить с собой разные зелья!!!";
        break;
    case 35:
        texte = "У жителей этой деревни очень необычный диалект, ничего невозможно понять...";
        break;
    case 36:
        texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+=";
        break;
    case 37:
        texte = "Сначала раздобудь разрешение Старосты, если хочешь пройти тут!!!";
        break;
    case 38:
        texte = "Староста разрешил тебе пройти??? Г-р-р-р... Проходи уже!!!";
        break;
    case 39:
        texte = "Прочь с дороги!!!";
        break;
    case 40:
        texte = "Здесь не принято принимать гостей.";
        break;
    case 41:
        texte = "Местные монстры не страшатся практически ничего, но к счастью, они нападают только на людей.";
        break;
    case 42:
        texte = "Серьезно?*Ты понял, что я только что сказал?";
        break;
    case 43:
        texte = "С: Пустыня и Деревня Герудо";
        break;
    case 44:
        texte = "Ю: Озеро Хайлия*З: Замок Хайрула";
        break;
    case 45:
        texte = "Какарико";
        break;
    case 46:
        texte = "З: Замок Хайрула";
        break;
    case 47:
        texte = "Какой чудесный день!!!";
        break;
    case 48:
        texte = "Зачем я только согласилась ухаживать за этим гадюшником???*Я терпеть не могу кур!!!";
        break;
    case 49:
        texte = "В магазине нашей деревни можно найти множество полезных вещей.";
        break;
    case 50:
        texte = "Ю: Какарико*З: Пустыня*В: Гора Смерти";
        break;
    case 51:
        texte = "Деревня Герудо";
        break;
    case 52:
        texte = "Заблудился в пустыне?*Ты здесь:*                        X";
        break;
    case 54:
        texte = "Ю: Замок Хайрула";
        break;
    case 55:
        texte = "Пустынный Храм**Приходите опробовать нашу купальню.*(вода непригодна для питья)";
        break;
    case 56:
        texte = "Лесной Храм**Спасите деревья, съешьте бобра!!!";
        break;
    case 57:
        texte = "Водный Храм**Всем обязательно иметь при себе шапочку для купания.";
        break;
    case 58:
        texte = "Ледяной Храм**Персонал напоминает вам, что здесь подземелье, а не каток.";
        break;
    case 59:
        texte = "Вы еще не видели кузнеца этой деревни?*Говорят, что он обладает огромным мастерством улучшать снаряжение искателей приключений, и у него очень много клиентов.";
        break;
    case 60:
        texte = "Храм находится в самой глубине пустыни, в древнем оазисе.";
        break;
    case 61:
        texte = "Ю: Огненные Земли*В: Какарико";
        break;
    case 62:
        texte = "Замок Хайрула";
        break;
    case 63:
        texte = "В: Какарико";
        break;
    case 64:
        texte = "З: Черепашья скала*В: Озеро Хайлия";
        break;
    case 65:
        texte = "Тайный Храм**Здесь покоится легендарный меч Сокрушитель Зла, Меч Мастера.";
        break;
    case 66:
        texte = "С: Кладбище с привидениями";
        break;
    case 67:
        texte = "Ты нашел Карту Подземелья!!!*Нажми L2, чтобы посмотреть на карту.";
        break;
    case 68:
        texte = "Ты нашел Компас!!!*Он покажет все сундуки и логово босса на твоей карте.";
        break;
    case 69:
        texte = "Ты нашел Ключ от Зала Босса!!!";
        break;
    case 70:
        texte = "Ты нашел небольшой ключ!!!*Подойди к двери, чтобы открыть ее.";
        break;
    case 71:
        texte = "Ты нашел Перчатки!!!*Используя их, ты сможешь поднимать и бросать предметы нажатием кнопки B.";
        break;
    case 72:
        texte = "Ты нашел Магический Кристалл!!!";
        tmp = 7 - gpJeu->getJoueur()->nbCristaux();
        os << tmp;
        if (tmp == 6 && !gpJeu->getJoueur()->getAvancement())
            buffer = "Для чего же он предназначен...?";
        else if (tmp > 2)
            buffer = "Осталось найти еще " + os.str() + "!!!";
        else if (tmp == 2)
            buffer = "Осталось найти еще два!!!";
        else if (tmp == 1)
            buffer = "Осталось найти еще один!!!";
        else if (tmp == 0)
            buffer = "Теперь у тебя есть все Кристаллы, скорее направляйся в Замок и спаси Зельду!!!";
        break;
    case 80:
        texte = "Ты нашел Гарпун!!!*Используй его, чтобы преодолевать препятствия.";
        break;
    case 81:
        texte = "Ты нашел Лампу!!!*Используй ее, чтобы зажечь огонь.*Для работы требуется топливо.";
        break;
    case 82:
        texte = "Ты нашел Ласты!!!*Приготовь их перед спуском в воду.";
        break;
    case 83:
        texte = "Ты нашел Магический Молот!!!*Используй его, чтобы разрушать преграды.";
        break;
    case 84:
        texte = "Ты нашел Огненный Жезл!!!*Отныне ты можешь извергать мощное пламя.";
        break;
    case 85:
        texte = "Ты нашел Ледяной Жезл!!!*Используй его, чтобы замораживать на расстоянии.";
        break;
    case 86:
        texte = "Ты нашел Меч Мастера!!!*Даже Ганон не может устоять перед его могуществом!!! (теоретически)";
        break;
    case 87:
        texte = "Поздравляю, Линк, тебе удалось спасти меня!!!***Давай быстрее найдем Ганона, мы должны вернуть Трифорс!";
        break;
    case 89:
        texte = "Секретный проход за тронным залом приведет тебя к Ганону. Поторопись!";
        break;
    case 90:
        texte = "Мы уже близко, за мной!";
        break;
    case 91:
        texte = "Боюсь, что ты не сможешь победить Ганона с твоим нынешним оружием...*Иди и поговори со старостой деревни Какарико, я уверен, он что-нибудь придумает.";
        break;
    case 92:
        texte = "Ганон прямо за этой дверью, я исцелю твои раны.";
        break;
    case 93:
        texte = "Ганон все еще где-то в замке.";
        break;
    case 94:
        texte = "Тебе стоит подождать принцессу Зельду!!!";
        break;
    case 95:
        texte = "Не возникало ли у тебя странного ощущения, что ты случайно про кого-то забыл???";
        break;
    case 96:
        texte = "Зельда ждет тебя!!!";
        break;
    case 97:
        texte = "Ты нашел Трифорс!!!";
        break;
    case 98:
        texte = "Ты нашел Книгу Мудоры!!!**Теперь ты понимаешь древний Хайлийский!!!";
        break;
    case 99:
        texte = "Поздравляю, Линк! Ты нашел меня и в награду я дарю тебе Кулон богини Дин, она повысит твою защиту на одно очко.";
        break;
    case 100:
        texte = "Поздравляю, Линк! Ты нашел меня и в награду я дарю тебе Кулон богини Нейрю, она повысит твою защиту на два очка!!!";
        break;
    case 101:
        texte = "...";
        break;
    case 102:
        texte = "Ты получил волшебный кулон!!!**Твоя защита увеличилась!!!";
        break;
    case 103:
        texte = "Поздравляю, Линк! Ты нашел меня и в награду я удвою твое максимальное количество магии!!!";
        break;
    case 104:
        texte = "Твое максимальное количество магии удвоено!!!";
        break;
    case 105:
        texte = "Возвращайтесь, когда у вас будет пустая бутылка, и я продам вам красное зелье, восстанавливающее здоровье.";
        break;
    case 106:
        texte = "Красное Зелье за 60 рупий, не интересует?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->hasBouteille(0) != 1 &&
            gpJeu->getJoueur()->hasBouteille(1) != 1 &&
            gpJeu->getJoueur()->hasBouteille(2) != 1)
        {
            id = 105;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 60)
            idsuiv = 29;
        else
            idsuiv = 108;
        break;
    case 107:
        texte = "Красное Зелье за 60 рупий, не интересует?**            да           ? НЕТ ?";
        break;
    case 108:
        texte = "Спасибо, вот ваше зелье.";
        break;
    case 109:
        texte = "Ты получил красное зелье!!!*Выпей его, чтобы восстановить здоровье!!!";
        break;
    case 110:
        texte = "Ты получил зеленое зелье!!!*Выпей его, чтобы восстановить магию!!!";
        break;
    case 111:
        texte = "Ты получил синее зелье!!!*Выпей его, чтобы восстановить здоровье и магию!!!";
        break;
    case 112:
        texte = "Здравствуйте, что вы хотели бы выпить?";
        break;
    case 113:
        texte = "-И-и-и-к!- Поговаривают, что фея одарит зачарованными предметами... -И-и-и-к!- ...того искателя приключений, что сможет найти ее... -И-и-и-к!!!-";
        break;
    case 114:
        texte = "Восполнить одно сердце за 10 рупий, устроит?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getVie() + gpJeu->getJoueur()->getBoostVie() == gpJeu->getJoueur()->getVieMax())
        {
            id = 128;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 10)
            idsuiv = 29;
        else
            idsuiv = 129;
        break;
    case 115:
        texte = "Восполнить одно сердце за 10 рупий, устроит?**            да           ? НЕТ ?";
        break;
    case 116:
        texte = "Чуточку магии за 20 рупий, не желаете?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() == gpJeu->getJoueur()->getMagieMax() ||
            !gpJeu->getJoueur()->hasObjet(O_LANTERNE))
        {
            id = 128;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 20)
            idsuiv = 29;
        else
            idsuiv = 129;
        break;
    case 117:
        texte = "Чуточку магии за 20 рупий, не желаете?**            да           ? НЕТ ?";
        break;
    case 118:
        texte = "Немного магии за 30 рупий, идет?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getMagie() + gpJeu->getJoueur()->getBoostMagie() == gpJeu->getJoueur()->getMagieMax() ||
            !gpJeu->getJoueur()->hasObjet(O_LANTERNE))
        {
            id = 128;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 30)
            idsuiv = 29;
        else
            idsuiv = 129;
        break;
    case 119:
        texte = "Немного магии за 30 рупий, идет?**            да           ? НЕТ ?";
        break;
    case 120:
        texte = "5 стрел за 30 рупий, возьмете?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax() ||
            !gpJeu->getJoueur()->hasObjet(O_ARC))
        {
            id = 128;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 30)
            idsuiv = 29;
        else
            idsuiv = 129;
        break;
    case 121:
        texte = "5 стрел за 30 рупий, возьмете?**            да           ? НЕТ ?";
        break;
    case 122:
        texte = "Одна бомба за 30 рупий, купите?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax() ||
            !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES))
        {
            id = 128;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 30)
            idsuiv = 29;
        else
            idsuiv = 129;
        break;
    case 123:
        texte = "Одна бомба за 30 рупий, купите?**            да           ? НЕТ ?";
        break;
    case 124:
        texte = "Лук за 1000 рупий, интересует?**          ? ДА ?           нет  ";
        idsuiv = 29;
        break;
    case 125:
        texte = "Лук за 1000 рупий, интересует?**            да           ? НЕТ ?";
        break;
    case 126:
        texte = "Лук за 50 рупий, берете?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 50)
            idsuiv = 29;
        else
            idsuiv = 129;
        break;
    case 127:
        texte = "Лук за 50 рупий, берете?**            да           ? НЕТ ?";
        break;
    case 128:
        texte = "Вам это сейчас ни к чему.";
        break;
    case 129:
        texte = "Благодарю.";
        break;
    case 130:
        texte = "Ты получил Лук!!!*Используй его, чтобы сразить цель на расстоянии.";
        break;
    case 131:
        texte = "Выбирайте то, что вам нужно.";
        break;
    case 132:
        texte = "Что??? У вас задание от нашего Старосты??? Хорошо... Я могу предложить скидку на этот замечательный лук.";
        break;
    case 133:
        texte = "Приветствую тебя, Линк. Я - Староста этой деревни. Я ждал, что ты придешь.";
        idsuiv = 134;
        break;
    case 134:
        texte = "С самого утра по Хайрулу шастают монстры, я попытался обсудить это с Зельдой, но, как ты, возможно, уже заметил, мощное заклинание заблокировало вход в замок...";
        idsuiv = 136;
        break;
    case 136:
        texte = "Говоришь, что Ганон виновен во всем случившемся? Что он украл Трифорс и держит в заточении принцессу Зельду?";
        idsuiv = 137;
        break;
    case 137:
        texte = "Хмм... Обстановка куда серьезнее, чем я думал...";
        idsuiv = 138;
        break;
    case 138:
        texte = "Мы должны действовать очень быстро, тебе предстоит снова встретиться с Ганоном!";
        idsuiv = 139;
        break;
    case 139:
        texte = "Как пройти в замок?*Есть у меня одна идея...";
        idsuiv = 140;
        break;
    case 140:
        texte = "Как ты знаешь, сила Семи Мудрецов была заперта в семи кристаллах волшебником Аганимом, когда он стремился открыть путь в Темный мир, где обитал Ганон.";
        idsuiv = 141;
        break;
    case 141:
        texte = "Но даже несмотря на то, что ты воскресил потомков Семи Мудрецов, одержав победу над Ганоном, и нашел Трифорс, эти кристаллы все еще сохранили свою силу.";
        idsuiv = 142;
        break;
    case 142:
        texte = "Они были сокрыты в глубине семи храмов. Собери их все, и ты сможешь разрушить чары Ганона.";
        idsuiv = 143;
        break;
    case 143:
        texte = "Однако это будет нелегко: Ганон наверняка отправит своих лучших воинов на защиту этих кристаллов...";
        idsuiv = 144;
        break;
    case 144:
        texte = "И последнее: со своим нынешним снаряжением ты далеко не пройдешь. Зайди к торговцу оружием и скажи, что ты пришел по моему поручению. Возможно, он сделает для тебя выгодное предложение.";
        break;
    case 145:
        texte = "Зайди к торговцу оружием и скажи, что ты пришел по моему поручению. Возможно, он сделает для тебя выгодное предложение.";
        break;
    case 146:
        texte = "Тебе предстоит собрать Семь кристаллов, чтобы обрести шанс спасти Зельду и весь Хайрул...";
        break;
    case 147:
        texte = "Ты нашел весь Семь кристаллов? Так что прямо сейчас отправляйся в замок, сначала тебе нужно вернуть принцессу, она лучше меня знает, как спасти Хайрул.";
        break;
    case 148:
        texte = "Твое оружие бессильно против Ганона? Тогда тебе нужно найти Меч Мастера. Говорят, что он был спрятан в тайном храме.*Кроме того, говорят, что путь, ведущий к мечу Сокрушителю Зла, лежит через деревню, населенную монстрами...*Интересно, существует ли подобная деревня...";
        break;
    case 150:
        texte = "Однако боюсь, что твоего нынешнего снаряжения не достаточно, чтобы добраться до этого храма, ты можешь посетить кузнеца деревни Герудо...";
        break;
    case 151:
        texte = "Пришло время сразиться с Ганоном и вернуть Трифорс!";
        break;
    case 152:
        texte = "Эй! Тебе следует заплатить, если хочешь открыть один из моих сундуков!!!";
        break;
    case 153:
        texte = "В одном из сундуков лежит частица сердца. Хотите испытать удачу за 10 рупий?*Можно открыть только один сундук.*          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 10)
            idsuiv = 29;
        break;
    case 154:
        texte = "В одном из сундуков лежит частица сердца. Хотите испытать удачу за 10 рупий?*Можно открыть только один сундук.*            да           ? НЕТ ?";
        break;
    case 155:
        texte = "Выбери сундук.";
        break;
    case 156:
        texte = "У меня больше нет призов, чтобы их разыграть, извините.";
        break;
    case 157:
        texte = "Ты проиграл! Этот сундук пуст. Попробуй еще!";
        break;
    case 158:
        texte = "Здравствуйте! Если вы ищете кузнеца, то он живет немного дальше.";
        break;
    case 159:
        texte = "Приветствую, Линк. Я - староста этой деревни.*Вам следует посетить нашего кузнеца и показать ему, чтобы вы хотели улучшить из своего снаряжения.";
        buffer = "Мне сообщили о вашем задании и я договорился с ним.*Для вас все будет бесплатно.";
        break;
    case 160:
        texte = "Сейчас вам не нужно пить это зелье.";
        break;
    case 161:
        texte = "Зеленое зелье за 40 рупий, вам это интересно?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->hasBouteille(0) != 1 &&
            gpJeu->getJoueur()->hasBouteille(1) != 1 &&
            gpJeu->getJoueur()->hasBouteille(2) != 1)
        {
            id = 163;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 40)
            idsuiv = 29;
        else
            idsuiv = 108;
        break;
    case 162:
        texte = "Зеленое зелье за 40 рупий, вам это интересно?**            да           ? НЕТ ?";
        break;
    case 163:
        texte = "Возвращайтесь, когда у вас будет пустая бутылка, и я продам вам зеленое зелье, восстанавливающее магию.";
        break;
    case 164:
        texte = "Приходите позже, сейчас у меня много работы!";
        break;
    case 165:
        texte = "Могу я что-нибудь сделать для вас?";
        if (gpJeu->getJoueur()->getEpee() == 1)
        {
            id = 166;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->hasObjet(O_GANTS) == 1 &&
            gpJeu->getJoueur()->getObjet() == 8)
        {
            id = 169;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->hasObjet(O_ARC) == 2 &&
            gpJeu->getJoueur()->getObjet() == 0 &&
            gpJeu->getJoueur()->nbCristaux() == 7)
        {
            id = 172;
            chercheText();
            break;
        }
        break;
    case 166:
        texte = "Хотите, чтобы я закалил ваш меч?**          ? ДА ?           нет  ";
        break;
    case 167:
        texte = "Хотите, чтобы я закалил ваш меч?**            да           ? НЕТ ?";
        break;
    case 168:
        texte = "Сила вашего меча увеличится втрое, и вы сможете нанести какую-нибудь магическую атаку, это очень здорово!!!";
        break;
    case 169:
        texte = "Хотите, чтобы я улучшил ваши перчатки?**          ? ДА ?           нет  ";
        break;
    case 170:
        texte = "Хотите, чтобы я улучшил ваши перчатки?**            да           ? НЕТ ?";
        break;
    case 171:
        texte = "Сила ваших перчаток позволит поднимать тяжелые камни.";
        break;
    case 172:
        texte = "Хотите, чтобы я улучшил ваш лук?**          ? ДА ?           нет  ";
        break;
    case 173:
        texte = "Хотите, чтобы я улучшил ваш лук?**            да           ? НЕТ ?";
        break;
    case 174:
        texte = "Теперь ваш лук стреляет серебряными стрелами с чудовищной силой!!!";
        break;
    case 175:
        texte = "Возвращайтесь, когда у вас будет пустая бутылка, и я смогу продать вам синее зелье, восстанавливающее здоровье и магию.";
        break;
    case 176:
        texte = "Синее зелье за 160 рупий, вас устраивает?**          ? ДА ?           нет  ";
        if (gpJeu->getJoueur()->hasBouteille(0) != 1 &&
            gpJeu->getJoueur()->hasBouteille(1) != 1 &&
            gpJeu->getJoueur()->hasBouteille(2) != 1)
        {
            id = 175;
            chercheText();
            break;
        }
        if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis() < 160)
            idsuiv = 29;
        else
            idsuiv = 108;
        break;
    case 177:
        texte = "Синее зелье за 160 рупий, вас устраивает?**            да           ? НЕТ ?";
        break;
    case 178:
        texte = "Наша деревня была здесь основана, чтобы не позволить беспечным искателям приключений попасть в храм. Я никого не пропущу.";
        break;
    case 179:
        texte = "Хммм... Вы уже нашли четыре кристалла?*Должен признать, вы произвели на меня впечатление...";
        buffer = "Хорошо, вам разрешено пересечь кладбище на свой страх и риск.";
        break;
    case 181:
        texte = "Поговорите со стражником на севере деревни, и он пропустит вас.";
        break;
    case 182:
        texte = "Я вижу, что вы еще живы...*Удивительно.";
        break;
    case 183:
        texte = "Темный Храм - это отправная точка на пути к легендарному предмету. Эта деревня существует лишь для того, чтобы отваживать искателей приключений от их дальнейшего пути к нему.";
        break;
    case 184:
        texte = "Итак, вы нашли Меч?*Но не думайте, что теперь он принадлежит вам.";
        buffer = "Меч Мастера - одно из самых ценнейших достояний Хайрула вместе с Трифорсом, и вам придется вернуть его обратно в святилище, когда ваша миссия будет завершена.";
        break;
    case 186:
        texte = "Все жители этой деревни - духи, откликнувшиеся на зов принцессы Зельды.";
        break;
    case 187:
        texte = "Когда вы вернули мир в Хайрул и воссоединили Светлый мир с Золотой землей, Зельда тайно попросила духов-добровольцев создать эту деревню, чтобы закрыть доступ к столь ценному предмету.";
        break;

    case 189:
        texte = "Добро пожаловать, Линк!*Позволь мне представить тебе то, чем я тут занимаюсь.";
        idsuiv = 190;
        break;
    case 190:
        texte = "Думаю, ты уже заметил, что монстры заполонили Хайрул. Впервые вижу здесь столько монстров с тех самых пор, как ты одолел Ганона.";
        idsuiv = 191;
        break;
    case 191:
        texte = "Что ж... Вот я и решил изучить их всех.";
        idsuiv = 192;
        break;
    case 192:
        texte = "Но, к сожалению, я очень боязливый и не могу встретиться с ними лицом к лицу, поэтому мне нужна твоя помощь.";
        idsuiv = 193;
        break;
    case 193:
        texte = "Тебе предстоит сразиться с монстром каждого вида и вернуться ко мне с отчетом.";
        idsuiv = 194;
        break;
    case 194:
        texte = "За каждую новую семерку изученных монстров я дам тебе в награду одну частицу сердца.";
        idsuiv = 195;
        break;
    case 195:
        texte = "Если желаешь посмотреть список побежденных монстров, то нажми L1.";
        break;

    case 196:
        if (gpJeu->getJoueur()->getCoeur(43))
        {
            if (gpJeu->getJoueur()->nbEnnemis() >= 46)
            {
                id = 205;
                chercheText();
                return;
            }
            else
            {
                id = 204;
                chercheText();
                return;
            }
        }
        for (int i = 38; i < 44; i++)
            if (!gpJeu->getJoueur()->getCoeur(i) &&
                (gpJeu->getJoueur()->nbEnnemis() / 7) + 37 >= i)
            {
                id = 203;
                chercheText();
                return;
            }
        tmp = 7 - (gpJeu->getJoueur()->nbEnnemis() % 7);
        os << tmp;
        if (tmp > 1)
            texte = "Срази еще " + os.str() + " разных монстров для получения новой награды.";
        else
            texte = "Тебе осталось сразить еще одного монстра для получения следующей награды!!!";
        break;
    case 203:
        texte = "Прими эту награду за свой вклад в мой проект!";
        break;
    case 204:
        texte = "Прошу простить меня, но мне больше нечего тебе подарить...";
        break;
    case 205:
        texte = "Я не могу в это поверить, но ты смог одолеть все виды монстров!!!*Прими мои поздравления, Линк!!!";
        break;

    case 206:
        texte = "                Уровень 1:**               Лесной Храм";
        break;
    case 207:
        texte = "                Уровень 2:**               Водный Храм";
        break;
    case 208:
        texte = "                Уровень 3:**               Горный Храм";
        break;
    case 209:
        texte = "                Уровень 4:**              Пустынный Храм";
        break;
    case 210:
        texte = "                Уровень 5:**               Темный Храм";
        break;
    case 211:
        texte = "                Уровень 6:**               Огненный Храм";
        break;
    case 212:
        texte = "                Уровень 7:**               Ледяной Храм";
        break;
    case 213:
        texte = "                Уровень ?:**               Тайный Храм";
        break;
    case 214:
        texte = "            Последний Уровень:**              Замок Хайрула";
        break;

    case 215:
        texte = "              Вы уже устали?                       ?     ВЕРНУТЬСЯ     ?                      Сохранить и выйти                        Выйти не сохраняя           ";
        break;
    case 216:
        texte = "              Вы уже устали?                             Вернуться                          ? СОХРАНИТЬ И ВЫЙТИ ?                      Выйти не сохраняя           ";
        break;
    case 217:
        texte = "              Вы уже устали?                             Вернуться                            Сохранить и выйти                      ? ВЫЙТИ НЕ СОХРАНЯЯ ?         ";
        break;

    case 223:
        texte = "В то время, как Линк коснулся Трифорса, монстры исчезли, и наступил мир.**И тогда принцесса Зельда приняла великое решение: она прикоснулась к Трифорсу и загадала свое желание.**Трифорс всегда был источником бед в Королевстве, рано или поздно его находило очередное порождение зла.**Как только принцесса прикоснулась к реликвии, она навсегда исчезла из Хайрула.";
        buffer = "С этого дня жители Хайрула живут в мире, не опасаясь новых бедствий.**Так возникла легенда о Зельде, Трифорсе и Золотой земле.**Меч Мастера, говорят, покоится в безопасном месте и должен оставаться последним напоминанием о приключениях Линка...";
        break;
    case 224:
        texte = "Поздравляю, Линк! Ты нашел меня и в качестве награды я дарю тебе Кулон богини Фароре. Он увеличит твою защиту на одно очко...";
        break;
    case 225:
        texte = "Хочешь сохранить игру сейчас?**                 ? ДА ?*                   нет  ";
        break;
    case 226:
        texte = "Хочешь сохранить игру сейчас?**                   да  *                 ? НЕТ ?";
        break;
    case 227:
        texte = "Игра сохранена.";
        break;

    case 228:
        texte = "Королевство Хайрул пребывает в мире с тех пор, как Линк, последний рыцарь Хайрула, победил злобного Ганона и отвоевал у него бесценный Трифорс.";
        idsuiv = 229;
        break;
    case 229:
        texte = "Никто не знает, какое желание загадал Линк Трифорсу, но в его последствии Светлый и Темный Миры воссоединились, а потомки Семи Мудрецов воскресли.";
        idsuiv = 230;
        break;
    case 230:
        texte = "Затем Линк передал Трифорс и Меч Мастера Принцессе Зельде и люди начали верить в то, что мир продлится долго.*Но, люди ошибались...";
        idsuiv = 231;
        break;
    case 231:
        texte = "К сожалению, желание Линка имело так же негативный эффект - Ганон и его приспешники воскресли и приготовились к новой атаке.";
        idsuiv = 232;
        break;
    case 232:
        texte = "Где-то в Лесах Хайрула спит Линк, ничего не подозревающий о том, что Ганон уже перешел в нападение, пока...*не услышал во сне такой хорошо знакомый голос...";
        break;
    case 233:
        texte = "На помощь!*Спасите!*Это я! Зельда!*Я говорю с тобой телепатически.";
        idsuiv = 234;
        break;
    case 234:
        texte = "Меня заточили в подземелье замка!*Мне нужна твоя помощь!*Ганон вернулся, и он наверняка уже нашел Трифорс...";
        idsuiv = 235;
        break;
    case 235:
        texte = "Скорее отправляйся в замок, Линк, ты - моя единственная надежда...";
        break;
    case 236:
        texte = "ПОМОЩЬ: Нажми SELECT, чтобы ознакомиться со справкой по игре.";
        break;
    }
}

void Texte::affiche(SDL_Surface *gpScreen, std::string s, int a, int b)
{
    afficheLettre(gpScreen, s, a, b);
}

void Texte::draw(SDL_Surface *gpScreen)
{
    if (cadre)
        drawCadre(gpScreen);

    if (id == 3)
    {
        SDL_Rect src;
        SDL_Rect dst;
        src.x = 16 * (gpJeu->getJoueur()->nbQuarts() % 4);
        if (src.x == 0)
            src.x = 16 * 4;
        src.y = 0;
        src.w = 16;
        src.h = 16;
        dst.x = 160 - 8;
        dst.y = 120 - 8 + 16 * 5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }

    int a = x + 8;
    int b = y + 8;
    for (int i = 0; i < av; i++)
    {
        afficheLettre(gpScreen, utf8utils::getChar(texte, i), a, b);
        a += charWidth;
        if (a > x + w - 16)
        {
            a = x + 8;
            b += 16;
        }
    }

    if (SDL_GetTicks() > lastAnimTime + vitesse &&
        def &&
        av < utf8utils::getLength(texte))
    {
        lastAnimTime = SDL_GetTicks();
        do
            av++;
        while (av < utf8utils::getLength(texte) &&
               utf8utils::getChar(texte, av - 1) == " ");
        if (utf8utils::getChar(texte, av - 1) != " ")
            gpJeu->getAudio()->playSound(0, 1);
    }
}

bool Texte::isFinished() { return (av == utf8utils::getLength(texte)); }

int Texte::getId() { return id; }

void Texte::changeId(int i)
{
    id = i;
    idsuiv = 0;
    buffer.clear();
    chercheText();
    decoupeText();
    if (av > utf8utils::getLength(texte))
        av = utf8utils::getLength(texte);
}

void Texte::drawCadre(SDL_Surface *gpScreen)
{
    SDL_Rect src;
    SDL_Rect dst;

    src.w = 8;
    src.h = 8;
    src.x = 103;
    src.y = 100;
    dst.x = x;
    dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);

    src.x = 112;
    for (int i = 8; i < w - 8; i += 16)
    {
        dst.x = x + i;
        src.w = 16;
        while (dst.x + src.w > x + w && src.w > 0)
            src.w--;
        if (src.w > 0)
            SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }

    src.w = 8;
    src.x = 129;
    dst.x = x + w - 8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);

    src.y = 109;
    src.w = 8;
    for (int j = 8; j < h - 8; j += 16)
    {
        dst.y = y + j;
        src.x = 103;
        dst.x = x;
        src.h = 16;
        while (dst.y + src.h > y + h && src.h > 0)
            src.h--;
        if (src.h > 0)
            SDL_BlitSurface(imageFont, &src, gpScreen, &dst);

        src.x = 129;
        dst.x = x + w - 8;
        if (src.h > 0)
            SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }

    src.h = 8;
    src.x = 103;
    src.y = 126;
    dst.x = x;
    dst.y = y + h - 8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);

    src.x = 112;
    for (int i = 8; i < w - 8; i += 16)
    {
        dst.x = x + i;
        src.w = 16;
        while (dst.x + src.w > x + w && src.w > 0)
            src.w--;
        if (src.w > 0)
            SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }

    src.w = 8;
    src.x = 129;
    dst.x = x + w - 8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit)
{
    if (idTxt == 0)
        return;
    id = idTxt;
    idsuiv = 0;
    buffer.clear();
    chercheText();

    x = vx;
    y = vy;
    w = vw;
    h = vh;
    decoupeText();

    def = defil;
    if (def)
        av = 0;
    else
        av = utf8utils::getLength(texte);

    cadre = cadr;

    vitesse = vit;
}

void Texte::decoupeText()
{
    // compte le nombre de caractères possibles et largeur et en hauteur
    int nbcol = (w - 16) / charWidth; // number of characters in a line
    int nblig = (h - 16) / 16;        // lines count
    int tailleMax = nbcol * nblig;    // total number of characters
    int taille;

    // parcours du texte a afficher; a chaque début de mot
    // vérifie que le mot peut tenir sur la ligne
    for (int i = 0; i < utf8utils::getLength(texte); i++)
    {
        // supprime les espaces isolès en dèbut de ligne
        if (utf8utils::getChar(texte, i) == " " &&
            utf8utils::getChar(texte, i + 1) != " " &&
            i % nbcol == 0)
        {
            utf8utils::removeChar(texte, i);
        }

        // recherche du dèbut du prochain mot
        while (utf8utils::getChar(texte, i) == " " &&
               i < utf8utils::getLength(texte) - 1)
            i++;

        // saute une ligne si trouve une ètoile
        if (utf8utils::getChar(texte, i) == "*")
        {
            utf8utils::removeChar(texte, i);
            int nb = (nbcol) - (i % (nbcol));
            for (int j = 0; j < nb; j++)
                utf8utils::insert(texte, i, " ");
            continue;
        }

        // si le mot dèpasse
        taille = tailleMot(i);
        if ((i % nbcol) + taille > nbcol)
        {
            if (i < tailleMax)
            {
                // si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille > nbcol)
                {
                    unsigned int pos = ((i / nbcol) + 1) * nbcol - 1;
                    utf8utils::insert(texte, pos, "--");
                    i = 1 + ((i / nbcol) + 1) * nbcol;
                }
                // sinon, on ajoute des espaces pour faire commencer le mot è la ligne
                else
                    while ((i % nbcol) != 0)
                    {
                        utf8utils::insert(texte, i, " ");
                        i++;
                    }
            }
        }
    }

    // si le texte est trop grand, on le coupe en deux
    if (utf8utils::getLength(texte) > tailleMax)
    {
        buffer = utf8utils::subStr(texte, tailleMax);
        utf8utils::eraseFrom(texte, tailleMax);
    }
}

int Texte::tailleMot(int deb)
{
    int i = deb;
    int total = 0;
    while (utf8utils::getChar(texte, i) != " ")
    {
        total++;
        i++;
        if (i >= utf8utils::getLength(texte))
            return total;
    }
    return total;
}

void Texte::afficheLettre(SDL_Surface *gpScreen, std::string c, int vx, int vy)
{
    SDL_Rect dst;

    dst.x = vx;
    dst.y = vy;

    SDL_Surface *textSurfaceBG = TTF_RenderUTF8_Solid(textFontBG, c.c_str(), textColorBG);
    SDL_BlitSurface(textSurfaceBG, NULL, gpScreen, &dst);
    SDL_FreeSurface(textSurfaceBG);

    dst.x++;
    dst.y++;

    SDL_Surface *textSurfaceFG = TTF_RenderUTF8_Solid(textFontFG, c.c_str(), textColorFG);
    SDL_BlitSurface(textSurfaceFG, NULL, gpScreen, &dst);
    SDL_FreeSurface(textSurfaceFG);
}

bool Texte::hasNext()
{
    return (!buffer.empty() || (idsuiv > 0));
}

bool Texte::suite()
{
    if (av < utf8utils::getLength(texte))
    {
        av = utf8utils::getLength(texte);
        return true;
    }
    if (!hasNext())
    {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (!buffer.empty())
    {
        texte = buffer;
        buffer.clear();
    }
    else
    {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def)
        av = 0;
    else
        av = utf8utils::getLength(texte);
    gpJeu->getAudio()->playSound(17);
    return true;
}