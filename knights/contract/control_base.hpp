#pragma once

class control_base {
protected:
    void assert_true(bool test, const char* cstr) {
        eosio_assert(test ? 1 : 0, cstr);
    }

    name to_name(account_name target) {
        name res;
        res.value = target;
        return res;
    }

    void validate_price(asset price, int grade) {
        assert_true(price.symbol == S(4,EOS) , "only EOS token allowed");
        assert_true(price.is_valid(), "invalid price");
        assert_true(price.amount > 0, "must price positive quantity");

        assert_true(price.amount >= get_min_market_price(grade), "too small price");
        assert_true(price.amount <= kv_max_market_price, "too big price");
    }

    int get_min_market_price(int grade) {
        int price = kv_min_market_price;
        int scaler = kv_min_market_price_scaler;
        
        if (grade >= ig_rare) {
            price *= (scaler & 0xF);
        } 
        if (grade >= ig_unique) {
            price *= ((scaler >> 4) & 0xF);
        } 
        if (grade >= ig_legendary) {
            price *= ((scaler >> 8) & 0xF);
        } 
        if (grade >= ig_ancient) {
            price *= ((scaler >> 12) & 0xF);
        }

        return price;
    }    
};

class drop_control_base : public control_base {
protected:
    int get_bottie(const player& player, int grade, random_val &rval) {
        int start = 0;
        int length = 0;

        double ndr[10] = {0.0, };
        switch (grade) {
            case ig_normal:
                start = 0;
                length = 4;
                break;
            case ig_rare:
                start = 4;
                length = 3;
                break;
            case ig_unique:
                start = 7;
                length = 2;
                break;
            case ig_legendary:
                start = 9;
                length = 1;
                break;
            case ig_ancient:
                start = 10;
                length = 1;
                break;
        }

        // copy drop rate
        double sum = 0;
        for (int index = 0; index < length; index++) {
            double value = drop_rates[start + index];
            sum += value;
            ndr[index] = value;
        }

        // normalize drop rate
        for (int index = 0; index < length; index++) {
            ndr[index] /= sum;
        }

        int best = 0;
        int drscale = 1000000000;
        int rand_value = rval.range(drscale);

        for (int index = length-1; index >= 1; --index) {
            if (rand_value < int(ndr[index] * drscale)) {
                best = index;
                break;
            }
        }

        int type = rval.range(5) + 1;
        int code = (type - 1) * 20 + (best + start + 1);
        return code;
    }    
};