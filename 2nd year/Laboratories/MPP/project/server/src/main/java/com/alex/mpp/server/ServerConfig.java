package com.alex.mpp.server;

import com.alex.mpp.common.service.AthleteService;
import com.alex.mpp.common.service.GameService;
import com.alex.mpp.common.service.ResultService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.remoting.rmi.RmiServiceExporter;

@Configuration
public class ServerConfig {
    private final GameService gameService;
    private final ResultService resultService;
    private final AthleteService athleteService;

    @Autowired
    public ServerConfig(GameService gameService, ResultService resultService, AthleteService athleteService) {
        this.gameService = gameService;
        this.resultService = resultService;
        this.athleteService = athleteService;
    }

    @Bean
    RmiServiceExporter athleteServiceRmiExporter() {
        RmiServiceExporter exporter = new RmiServiceExporter();
        exporter.setServiceInterface(AthleteService.class);
        exporter.setServiceName(AthleteService.class.getSimpleName());
        exporter.setService(athleteService);
        return exporter;
    }

    @Bean
    RmiServiceExporter gameServiceRmiExporter() {
        RmiServiceExporter exporter = new RmiServiceExporter();
        exporter.setServiceInterface(GameService.class);
        exporter.setServiceName(GameService.class.getSimpleName());
        exporter.setService(gameService);
        return exporter;
    }

    @Bean
    RmiServiceExporter resultServiceRmiExporter() {
        RmiServiceExporter exporter = new RmiServiceExporter();
        exporter.setServiceInterface(ResultService.class);
        exporter.setServiceName(ResultService.class.getSimpleName());
        exporter.setService(resultService);
        return exporter;
    }
}
