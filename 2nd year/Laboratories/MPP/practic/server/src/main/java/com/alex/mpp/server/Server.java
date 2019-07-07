package com.alex.mpp.server;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@EntityScan("com.alex.mpp.data")
@EnableJpaRepositories("com.alex.mpp.data")
@SpringBootApplication(
        scanBasePackages = {
                "com.alex.mpp.server",
                "com.alex.mpp.data"
        }
)
public class Server {
    public static void main(String[] args) {
        SpringApplication.run(Server.class, args);
    }
}
