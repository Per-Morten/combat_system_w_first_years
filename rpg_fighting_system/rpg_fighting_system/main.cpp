// "color_scheme": "Packages/Color Scheme - pm_theme/pm_theme.sublime-color-scheme",
#include <iostream>
#include <cctype>
#include <random>
#include <ctime>

enum Type
{
    RODENT,
    SLIME,
    ORC,
};

struct BaseStats
{
    int hp;
    int maxHP;
    int mp;
    int maxMP;
    int attackPower;
};

struct Creature
{
    BaseStats stats;
    Type type;
};

struct Spell
{
    int cost;
    int damage;
};

struct Player
{
    BaseStats stats;
    Spell fireball;
    int healthPotions;
};

Creature createCreature(int maxHP, int maxMP, int attackPower, Type type)
{
    Creature m;
    m.stats.hp = maxHP;
    m.stats.maxHP = maxHP;
    m.stats.mp = maxMP;
    m.stats.maxMP = maxMP;
    m.type = type;

    m.stats.attackPower = attackPower;

    return m;
}

void printStats(BaseStats stats)
{
    std::cout << " HP: " << stats.hp << "/" << stats.maxHP << "\n"
        << " MP: " << stats.mp << "/" << stats.maxMP << "\n";
}

void hangWindow()
{
    std::cout << "Press enter to continue\n";
    char buffer[2];
    std::cin.ignore();
    std::cin.getline(buffer, 1);
}

int
main()
{
    // Combat screen
    // EnemyHP
    // EnemyMP
    // PlayerHP
    // PlayerMP
    // Attack alternatives
    // Enemy attacks (Random)
    // Victory/Defeat message

    Player player;
    player.stats.maxHP = 10;
    player.stats.hp = player.stats.maxHP;
    player.stats.maxMP = 500;
    player.stats.mp = player.stats.maxMP;
    player.healthPotions = 2;
    player.stats.attackPower = 3;
    player.fireball.damage = 5;
    player.fireball.cost = 250;

    Creature rat = createCreature(30, 2, 2, Type::RODENT);

    while (player.stats.hp > 0 && rat.stats.hp > 0)
    {
        player.stats.mp += 5;
        if (player.stats.mp >= player.stats.maxMP)
            player.stats.mp = player.stats.maxMP;

        std::cout << "Battle Screen:\n";
        std::cout << "Player\n";
        printStats(player.stats);

        std::cout << "Rat\n";
        printStats(rat.stats);

        srand(time(NULL));

        std::cout << "What do you want to do?\n";
        std::cout << "1. Hit regular\n"
            << "2. Firemagic\n"
            << "3. Drink healthpotion\n";

        int choice = 0;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            rat.stats.hp -= player.stats.attackPower;
            std::cout << "You hit the rat dealing " << player.stats.attackPower << " damage\n";
            break;
        case 2:
            if (player.stats.mp >= player.fireball.cost)
            {
                std::cout << "You cast fireball at rat dealing " << player.fireball.damage << " damage\n";
                rat.stats.hp -= player.fireball.damage;
                player.stats.mp -= player.fireball.cost;
            }
            else
            {
                std::cout << "You do not have enough mana to cast a fireball: " << player.fireball.cost << "\n";
            }

            break;
        case 3:
            if (player.healthPotions > 0)
            {
                player.healthPotions--;
                player.stats.hp += 5;
                if (player.stats.hp >= player.stats.maxHP)
                {
                    player.stats.hp = player.stats.maxHP;
                }
                std::cout << "You drink a health potion, healing 5 hp\n";
            }
            else
            {
                std::cout << "You do not have any health potions left\n";
            }
            break;
        default:
            break;
        }

        int ratChoice = std::rand() % 2;
        switch (ratChoice)
        {
        case 0:
            player.stats.hp -= rat.stats.attackPower;
            std::cout << "The rat hits you dealing " << rat.stats.attackPower << " damage\n";
            break;
        case 1:
            if (rat.stats.hp >= rat.stats.maxHP / 2)
            {
                player.stats.hp -= rat.stats.attackPower * 2;
                std::cout << "The rat hits you really hard dealing " << rat.stats.attackPower * 2 << " damage\n";
            }
            break;
        }
    }

    if (rat.stats.hp <= 0 && player.stats.hp <= 0)
    {
        std::cout << "You both fall over each other dead\n";
    }
    else if (rat.stats.hp <= 0)
    {
        std::cout << "You stand victorious over the dead rat\n";
    }
    else if (player.stats.hp <= 0)
    {
        std::cout << "You have been defeated by a puny rat\n";
    }

    hangWindow();


    return 0;
}


// Tasks:
//  Rat does damage
//  Player can use health potions (no more than the ones they have available)
//  Player regains some mana on each turn
//  Add hit-chance based on stats & randomness
//  Fight multiple monsters
//  Game over/victory screen
//  Allow for multiple fights
//  End of battle screen


