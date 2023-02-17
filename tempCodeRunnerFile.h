if (countPlus > 0 && countMinus == 0) {
        for (auto url1 : spaceURL) { 
            for (auto url2 : plusURL) {
                if (url1 == url2) {
                    result.insert(url2);
                }
            }
        }
    }