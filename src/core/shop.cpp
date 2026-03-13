#include "shop.h"
#include "input.h"
#include <iostream>
#include <thread>

Shop::Shop(const std::string& name) : Location(name, location_Type::Friendly, 1) {}

void Shop::addWeapon(std::unique_ptr<Weapon> item) { allWeapons.push_back(std::move(item)); }
void Shop::addArmor(std::unique_ptr<Armor> item) { allArmors.push_back(std::move(item)); }
void Shop::addPotion(std::unique_ptr<HealthPotion> item) { allPotions.push_back(std::move(item)); }

void Shop::enter(Player& player) {
    bool inShop = true;
    while (inShop) {
        clearScreen();
        std::cout << "\n=== Shop ===\n";
        std::cout << "Your money: " << player.getMoney() << "\n";
        std::cout << "1. Buy weapons\n2. Buy armour\n3. Buy potions\n4. Exit shop\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::vector<Weapon*> available;
            for (auto& w : allWeapons)
                if (w->getMinLevel() <= player.getLevel())
                    available.push_back(w.get());
            if (available.empty()) {
                std::cout << "No weapons available.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            for (size_t i = 0; i < available.size(); ++i)
                std::cout << i << ": " << available[i]->getName() << " (damage " << available[i]->getDamage()
                << ", price " << available[i]->getPrice() << ")\n";
            std::cout << "Enter index to buy, -1 to cancel: ";
            int idx; std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int>(available.size())) {
                Weapon* selected = available[idx];
                if (player.getMoney() >= selected->getPrice()) {
                    player.spendMoney(selected->getPrice());
                    if (selected->getTypeName() == "Sword") {
                        auto* s = dynamic_cast<Sword*>(selected);
                        player.addWeapon(std::make_unique<Sword>(s->getName(), s->getDamage(), s->getAccuracy(), s->getPrice(), s->getMinLevel()));
                    }
                    else if (selected->getTypeName() == "Bow") {
                        auto* b = dynamic_cast<Bow*>(selected);
                        player.addWeapon(std::make_unique<Bow>(b->getName(), b->getDamage(), b->getAccuracy(), b->getPrice(), b->getMinLevel()));
                    }
                    else if (selected->getTypeName() == "Morgenstern") {
                        auto* m = dynamic_cast<Morgenstern*>(selected);
                        player.addWeapon(std::make_unique<Morgenstern>(m->getName(), m->getDamage(), m->getAccuracy(), m->getBleeding(), m->getPrice(), m->getMinLevel()));
                    }
                    player.equipWeapon(static_cast<int>(player.getWeaponCount()) - 1);
                    std::cout << "Purchased and equipped.\n";
                }
                else {
                    std::cout << "Not enough money.\n";
                }
            }
        }
        else if (choice == 2) {
            std::vector<Armor*> available;
            for (auto& a : allArmors)
                if (a->getMinLevel() <= player.getLevel())
                    available.push_back(a.get());
            if (available.empty()) {
                std::cout << "No armour available.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            for (size_t i = 0; i < available.size(); ++i)
                std::cout << i << ": " << available[i]->getName() << " (defense " << available[i]->getDefense()
                << ", price " << available[i]->getPrice() << ")\n";
            std::cout << "Enter index to buy, -1 to cancel: ";
            int idx; std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int>(available.size())) {
                Armor* selected = available[idx];
                if (player.getMoney() >= selected->getPrice()) {
                    player.spendMoney(selected->getPrice());
                    if (selected->getType() == "Helmet") {
                        auto* h = dynamic_cast<Helmet*>(selected);
                        player.addArmor(std::make_unique<Helmet>(h->getName(), h->getDefense(), h->getProjectileDefense(), h->getPrice(), h->getMinLevel()));
                        player.equipHelmet(static_cast<int>(player.getArmorCount()) - 1);
                    }
                    else if (selected->getType() == "Chestplate") {
                        auto* c = dynamic_cast<Chestplate*>(selected);
                        player.addArmor(std::make_unique<Chestplate>(c->getName(), c->getDefense(), c->getPrice(), c->getMinLevel()));
                        player.equipChestplate(static_cast<int>(player.getArmorCount()) - 1);
                    }
                    std::cout << "Purchased and equipped.\n";
                }
                else {
                    std::cout << "Not enough money.\n";
                }
            }
        }
        else if (choice == 3) {
            std::vector<HealthPotion*> available;
            for (auto& p : allPotions)
                if (p->getMinLevel() <= player.getLevel())
                    available.push_back(p.get());
            if (available.empty()) {
                std::cout << "No potions available.\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            for (size_t i = 0; i < available.size(); ++i)
                std::cout << i << ": " << available[i]->getType() << " (heal " << available[i]->getHeal()
                << ", price " << available[i]->getCost() << ")\n";
            std::cout << "Enter index to buy, -1 to cancel: ";
            int idx; std::cin >> idx;
            if (idx >= 0 && idx < static_cast<int>(available.size())) {
                HealthPotion* selected = available[idx];
                if (player.getMoney() >= selected->getCost()) {
                    player.spendMoney(selected->getCost());
                    player.addStuff(std::make_unique<HealthPotion>(selected->getType(), selected->getCost(), selected->getHeal(), selected->getMinLevel()));
                    std::cout << "Purchased.\n";
                }
                else {
                    std::cout << "Not enough money.\n";
                }
            }
        }
        else if (choice == 4) {
            inShop = false;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}