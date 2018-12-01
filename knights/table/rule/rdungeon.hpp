#pragma once

//@abi table rdungeon i64
struct rdungeon {
    uint64_t code = 0;
    uint8_t wave = 0;
    uint8_t fee = 0;
    uint16_t required_floor = 0;
    uint16_t unique_drop = 0;
    uint16_t legendary_drop = 0;
    uint8_t unit_count1 = 0;
    uint8_t unit_count2 = 0;
    uint8_t unit_count3 = 0;
    uint16_t mat1 = 0;
    uint16_t mat2 = 0;
    uint16_t mat3 = 0;
    uint16_t mdrop1 = 0;
    uint16_t mdrop2 = 0;
    uint16_t mdrop3 = 0;
    uint64_t v1 = 0;
    uint64_t v2 = 0;

    rdungeon() {
    }

    uint64_t primary_key() const {
        return code;
    }

    EOSLIB_SERIALIZE(
            rdungeon,
            (code)
            (wave)
            (fee)
            (required_floor)
            (unique_drop)
            (legendary_drop)
            (unit_count1)
            (unit_count2)
            (unit_count3)
            (mat1)
            (mat2)
            (mat3)
            (mdrop1)
            (mdrop2)
            (mdrop3)
            (v1)
            (v2)
    )
};

typedef eosio::multi_index< N(rdungeon), rdungeon> rdungeon_table;
