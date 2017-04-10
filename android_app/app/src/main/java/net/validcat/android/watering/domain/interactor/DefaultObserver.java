package net.validcat.android.watering.domain.interactor;

import io.reactivex.observers.DisposableObserver;

/**
 * Default {@link DisposableObserver} base class to be used whenever you want default error handling.
 */

public class DefaultObserver<T> extends DisposableObserver<T> {

    @Override public void onNext(T value) {}
    @Override public void onError(Throwable e) {}
    @Override public void onComplete() {}
}
