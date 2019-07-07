package com.alex.mpp.client;

import com.alex.mpp.common.service.AthleteService;
import com.alex.mpp.common.service.GameService;
import com.alex.mpp.common.service.ResultService;
import com.alex.mpp.common.util.SocketManager;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.remoting.rmi.RmiProxyFactoryBean;

@Configuration
public class ClientConfig {
    @Bean
    RmiProxyFactoryBean athleteServiceRmiProxy() {
        RmiProxyFactoryBean factory = new RmiProxyFactoryBean();
        factory.setServiceInterface(AthleteService.class);
        factory.setServiceUrl(
                "rmi://" + SocketManager.getServerHost() + ":1099" +
                        "/" + AthleteService.class.getSimpleName()
        );
        return factory;
    }

    @Bean
    RmiProxyFactoryBean gameServiceRmiProxy() {
        RmiProxyFactoryBean factory = new RmiProxyFactoryBean();
        factory.setServiceInterface(GameService.class);
        factory.setServiceUrl(
                "rmi://" + SocketManager.getServerHost() + ":1099" +
                        "/" + GameService.class.getSimpleName()
        );
        return factory;
    }

    @Bean
    RmiProxyFactoryBean resultServiceRmiProxy() {
        RmiProxyFactoryBean factory = new RmiProxyFactoryBean();
        factory.setServiceInterface(ResultService.class);
        factory.setServiceUrl(
                "rmi://" + SocketManager.getServerHost() + ":1099" +
                        "/" + ResultService.class.getSimpleName()
        );
        return factory;
    }
}
