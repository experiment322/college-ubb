package factory;

import model.Container;

public interface Factory {
    Container createContainer(Strategy startegy);
}

