#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {

    if (fuel <= 0) {
        printf("Planet %d: Fuel Remaining = 0\n", planet);
        printf("Mission Failed!\n");
        return 0;
    }

    if (planet > totalPlanets) {
        printf("Mission Successful!\n");
        return fuel;
    }

    fuel -= consumption;
    fuel += recharge;

    if (planet % 4 == 0) {
        fuel += solarBonus;
    }

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int fuel, consumption, recharge, solarBonus, totalPlanets;

    printf("Enter initial fuel: ");
    scanf("%d", &fuel);

    printf("Enter fuel consumption per planet: ");
    scanf("%d", &consumption);

    printf("Enter gravitational recharge per planet: ");
    scanf("%d", &recharge);

    printf("Enter solar recharge bonus every 4th planet: ");
    scanf("%d", &solarBonus);

    printf("Enter total planets: ");
    scanf("%d", &totalPlanets);

    printf("\n--- Spacecraft Journey Simulation ---\n");

    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}
