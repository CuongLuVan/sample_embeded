using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ThreadMessaging.Messages;

namespace ThreadMessaging
{
    /// <summary>
    /// Manages threads that use the inter-thread messaging scheme
    /// </summary>
    public class ThreadManager : IThreadManager
    {
        /// <summary>
        /// Thread Manager instance
        /// </summary>
        private static ThreadManager threadManager = null;

        /// <summary>
        /// Create a trhead manager instance and return the reference
        /// </summary>
        /// <returns></returns>
        public static ThreadManager GetThreadManager()
        {
            threadManager = new ThreadManager();
            return threadManager;
        }

        /// <summary>
        /// The managed threads
        /// </summary>
        private Dictionary<string, IThread> threads;

        /// <summary>
        /// Create a managed thread to receive messages for the client using this object
        /// </summary>
        private ManagedThread clientReceiveThread;

        /// <summary>
        /// Instance constructor
        /// </summary>
        private ThreadManager()
        {
            threads = new Dictionary<string, IThread>();

            // Create a managed thread and queue to receive messages for the client
            clientReceiveThread = new ManagedThread("ClientReceiveThread", messageHandler);
        }

        /// <summary>
        /// Client received message handler
        /// </summary>
        /// <param name="msg"></param>
        private void messageHandler(BaseMessage msg)
        {
            if (ReceivedMessage != null)
                ReceivedMessage(msg);
        }

        #region IThreadManager Implementation
        /// <summary>
        /// Create a thread, it must be started running separately.
        /// This method pends at the message queue until a message arrives and then
        /// calls your message handler.
        /// </summary>
        /// <param name="threadName"></param>
        /// <returns></returns>
        public IThread CreateThread(string threadName, Action<BaseMessage> messageHandler)
        {
            ManagedThread thrd = new ManagedThread(threadName,  messageHandler);
            threads.Add(threadName, thrd);
            return thrd;
        }

        /// <summary>
        /// Create a thread, it must be started running separately.
        /// This method pends at the message queue until either a message arrives or the time
        /// out period expires and then calls your message handler. If a time out the handler
        /// is called with a null instead of a message object.
        /// </summary>
        /// <param name="threadName"></param>
        /// <returns></returns>
        public IThread CreateThread(
            string threadName,
            Action<BaseMessage> messageHandler,
            int waitTimeInMilliseconds)
        {
            ManagedThread thrd = new ManagedThread(threadName, messageHandler, waitTimeInMilliseconds);
            threads.Add(threadName, thrd);
            return thrd;
        }

        /// <summary>
        /// Get a list of all the threads under management
        /// </summary>
        /// <returns></returns>
        public List<IThread> GetThreads()
        {
            return threads.Values.ToList();
        }

        /// <summary>
        /// Start all threads running
        /// </summary>
        public void StartAllThreads()
        {
            clientReceiveThread.StartThread();
            foreach (ManagedThread t in threads.Values)
                t.StartThread();
        }

        /// <summary>
        /// Stop all threads
        /// </summary>
        public void StopAllThreads()
        {
            foreach (ManagedThread t in threads.Values)
                t.StopThread();
            clientReceiveThread.StopThread();
        }

        /// <summary>
        /// Removes all threads from the manager
        /// </summary>
        public void ClearAllThreads()
        {
            threads = new Dictionary<string, IThread>();
        }

        /// <summary>
        /// Send a message to the thread that created the Thread Manager
        /// </summary>
        /// <param name="msg"></param>
        public void SendMessage(BaseMessage msg)
        {
            clientReceiveThread.SendMessage(msg);
        }

        /// <summary>
        /// Clients of this object that want to receive messages from their managed threads
        /// should wire in this event.
        /// </summary>
        public event Action<BaseMessage> ReceivedMessage;
        #endregion
    }
}
