#ifndef ALLOC_MELT_CARD_DATA_H
#define ALLOC_MELT_CARD_DATA_H

struct CardsNumericData;

void distributeIndexInCardArray(struct CardsNumericData *cardsData, unsigned int pairNumber);

void setLinearCardsValue(struct CardsNumericData *cardsData, unsigned int pairNumber);

void meltCardsValueData(struct CardsNumericData *cardsData, unsigned int pairNumber);

void initMiscellaneous(struct CardsNumericData* cardsData, unsigned int pairNumber);

void freeMemoryAllocations(struct CardsNumericData* cardsData);

#endif //ALLOC_MELT_CARD_DATA_H