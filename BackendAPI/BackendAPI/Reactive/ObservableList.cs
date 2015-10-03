using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

namespace VSP.Reactive {
    /// <summary>
    /// An observable list. It fires events when being updated or elements are changed.
    /// </summary>
    /// <typeparam name="T">The type of the elements in the list.</typeparam>
    [Serializable]
    public class ObservableList<T> : List<T> {
        public event Action<int> ChangedElement = delegate { };

        ///The Updated Action fires an incorrect event: CS0067, "Updated" is never used
        #pragma warning disable 0067
        public event Action Updated = delegate { };
        #pragma warning restore 0067

        public ObservableList() : base() { }
        public ObservableList(int capacity) : base(capacity) { }
        public ObservableList(IEnumerable<T> collection) : base(collection) { }

        public new void Add(T item) {
            base.Add(item);
            Updated();
        }
        public new void Remove(T item) {
            base.Remove(item);
            Updated();
        }
        public new void AddRange(IEnumerable<T> collection) {
            base.AddRange(collection);
            Updated();
        }
        public new void RemoveRange(int index, int count) {
            base.RemoveRange(index, count);
            Updated();
        }
        public new void Clear() {
            base.Clear();
            Updated();
        }
        public new void Insert(int index, T item) {
            base.Insert(index, item);
            Updated();
        }
        public new void InsertRange(int index, IEnumerable<T> collection) {
            base.InsertRange(index, collection);
            Updated();
        }
        public new void RemoveAll(Predicate<T> match) {
            base.RemoveAll(match);
            Updated();
        }
        public new void RemoveAt(int index) {
            base.RemoveAt(index);
            Updated();
        }

        public new T this[int index] {
            get {
                return base[index];
            }
            set {
                base[index] = value;
                Updated();
                ChangedElement(index);
            }
        }
    }
}
