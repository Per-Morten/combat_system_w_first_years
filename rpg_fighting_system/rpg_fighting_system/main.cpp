// "color_scheme": "Packages/Color Scheme - pm_theme/pm_theme.sublime-color-scheme",
#include <iostream>
#include <cctype>
#include <random>
#include <ctime>
#include <vector>
#include <string>

enum Type
{
    RODENT,
    SLIME,
    ORC,
    HUMAN,
    DWARF,
    ELF,
};

struct BaseStats
{
    int hp;
    int maxHP;
    int mp;
    int maxMP;
    int attackPower;
};

enum ActionType
{
    SPELL,
    USE_ITEM,
    ATTACK,
};

struct Action
{
    ActionType type;
    int cost;
    int damage;
    std::string name;
};

struct Creature
{
    BaseStats stats;
    Type type;
    std::vector<Action> actions;
};


Creature createCreature(int maxHP, int maxMP, int attackPower, Type type)
{
    Creature m;
    m.stats.hp = maxHP;
    m.stats.maxHP = maxHP;
    m.stats.mp = maxMP;
    m.stats.maxMP = maxMP;
    m.type = type;

    Action attack;
    attack.cost = 0;
    attack.damage = attackPower;
    attack.name = "Regular attack";
    attack.type = ActionType::ATTACK;
    m.actions.push_back(attack);

    return m;
}

Creature createPlayer()
{
    Creature player = createCreature(20, 200, 10, Type::HUMAN);

    Action fireball;
    fireball.cost = 10;
    fireball.damage = 50;
    fireball.type = ActionType::SPELL;
    fireball.name = "Fireball";
    player.actions.push_back(fireball);

    Action icebeam;
    icebeam.cost = 10;
    icebeam.damage = 50;
    icebeam.type = ActionType::SPELL;
    icebeam.name = "Icebeam";
    player.actions.push_back(icebeam);

    Action healthPotion;
    healthPotion.cost = 5;
    healthPotion.damage = 10;
    healthPotion.name = "Minor Health Potion";
    healthPotion.type = ActionType::USE_ITEM;
    player.actions.push_back(healthPotion);

    return player;
}

void printStats(BaseStats stats)
{
    std::cout << " HP: " << stats.hp << "/" << stats.maxHP << "\n"
        << " MP: " << stats.mp << "/" << stats.maxMP << "\n";
}

std::string stringifyType(Type type)
{
    switch (type)
    {
    case Type::ORC:
        return "Orc";
        break;
    case Type::RODENT:
        return "Rodent";
        break;
    case Type::SLIME:
        return "Slime";
        break;
    case Type::HUMAN:
        return "Human";
        break;
    case Type::DWARF:
        return "Dwarf";
        break;
    case Type::ELF:
        return "Elf";
        break;
    }
    return "";
}

void executeAction(Creature& executor, Action& action, Creature& target)
{
    if (action.type == ActionType::ATTACK)
    {
        target.stats.hp -= action.damage;
        std::cout << stringifyType(executor.type) << " hit the " << stringifyType(target.type) << " dealing " << action.damage << " damage\n";
    }
    else if (action.type == ActionType::SPELL)
    {
        if (executor.stats.mp >= action.cost)
        {
            target.stats.hp -= action.damage;
            executor.stats.mp -= action.damage;
            std::cout << stringifyType(executor.type) << " hit the " << stringifyType(target.type) << " with " << action.name << " dealing " << action.damage << " damage\n";
        }
        else
        {
            std::cout << "You do not have enough mana to cast a " << action.name << ": " << action.cost << "\n";
        }
    }
    else if (action.type == ActionType::USE_ITEM)
    {
        if (action.cost-- > 0)
        {
            executor.stats.hp += action.damage;
            if (executor.stats.hp >= executor.stats.maxHP)
                executor.stats.hp = executor.stats.maxHP;
        }
        else
        {
            std::cout << "You don't have enough health potions\n";
        }
    }
}

bool combat(Creature& player, Creature& enemy)
{
    std::string enemyType = stringifyType(enemy.type);

    while (player.stats.hp > 0 && enemy.stats.hp > 0)
    {
        player.stats.mp += 5;
        if (player.stats.mp >= player.stats.maxMP)
            player.stats.mp = player.stats.maxMP;

        std::cout << "Battle Screen:\n";
        std::cout << "Player\n";
        printStats(player.stats);

        std::cout << enemyType << "\n";
        printStats(enemy.stats);

        srand(time(NULL));

        for (int i = 0; i < player.actions.size(); i++)
        {
            std::cout << i << ". " << player.actions[i].name << "\n";
        }

        int choice = 0;
        std::cin >> choice;

        if (choice < player.actions.size() && choice >= 0)
        {
            executeAction(player, player.actions[choice], enemy);
        }

        int enemyChoice = std::rand() % enemy.actions.size();
        if (enemyChoice < enemy.actions.size() && choice >= 0)
        {
            executeAction(enemy, enemy.actions[enemyChoice], player);
        }
    }

    return player.stats.hp > 0;
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
    Creature player = createPlayer();

    Creature rat = createCreature(10, 2, 2, Type::RODENT);
    Creature orc = createCreature(30, 100, 2, Type::ORC);
    
    Action fireball;
    fireball.cost = 10;
    fireball.damage = 50;
    fireball.type = ActionType::SPELL;
    fireball.name = "Fireball";
    orc.actions.push_back(fireball);

    std::vector<Creature> creatures;
    creatures.push_back(rat);
    creatures.push_back(orc);

    for (int i = 0; i < creatures.size(); i++)
    {
        bool result = combat(player, creatures[i]);
        if (result)
        {
            std::cout << "You stand victorious over the dead " << stringifyType(creatures[i].type) << "\n";
        }
        else
        {
            std::cout << "You have been defeated by a puny " << stringifyType(creatures[i].type) << "\n";
            break;
        }
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


