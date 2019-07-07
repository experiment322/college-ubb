package com.alex.mpp.common.service;

import com.alex.mpp.data.domain.Referee;

public interface RefereeService {
    Referee authenticate(String username, String password);
}
