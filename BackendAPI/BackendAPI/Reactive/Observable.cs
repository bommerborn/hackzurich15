using System;
using System.Collections.Generic;

namespace BackendAPI.Reactive {
    /// <summary>
    /// A class for creating a Observable value. When the value changes an event is triggered.
    /// </summary>
    /// <typeparam name="T">The type of the value</typeparam>
    public class Observable<T> {

        Action<T> OnChange = delegate { };

        Action<T, T> OnChangeWithPrevious = delegate { };

        private T observableValue;

        public bool HasValue {
            get { return Value != null; }
        }

        public T Value {
            get { return observableValue; }
            set {
                if (observableValue != null &&
                    EqualityComparer<T>.Default.Equals(observableValue, value)) {
                    return;
                }

                T previousValue = observableValue;

                observableValue = value;

                OnChange(observableValue);
                OnChangeWithPrevious(previousValue, observableValue);
            }
        }

        public Observable() {

        }

        public Observable(T initialValue) {
            observableValue = initialValue;
        }

        /// <summary>
        /// Subscribe to a value change
        /// </summary>
        /// <param name="action">The delegate to execute when a value has changed. Parameter passed is new value</param>
        public void Subscribe(Action<T> action) {
            OnChange += action;
        }

        /// <summary>
        /// Subscribe to a value change
        /// </summary>
        /// <param name="action">The delegate to execute when a value has changed. Parameters passed are old and new value</param>
        public void Subscribe(Action<T, T> action) {
            OnChangeWithPrevious += action;
        }
    }
}
