using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ThreadMessaging.Messages;

namespace ThreadMessaging
{
    /// <summary>
    /// Interface to the thread manager
    /// </summary>
    public interface IThreadManager
    {
        /// <summary>
        /// Create a thread, it must be started running separately.
        /// This method pends at the message queue until a message arrives and then
        /// calls your message handler.
        /// </summary>
        /// <param name="threadName"></param>
        /// <returns></returns>
        IThread CreateThread(string threadName, Action<BaseMessage> messageHandler);

        /// <summary>
        /// Create a thread, it must be started running separately.
        /// This method pends at the message queue until either a message arrives or the time
        /// out period expires and then calls your message handler. If a time out the handler
        /// is called with a null instead of a message object.
        /// </summary>
        /// <param name="threadName"></param>
        /// <returns></returns>
        IThread CreateThread(
            string threadName, 
            Action<BaseMessage> messageHandler,
            int waitTimeInMilliseconds);

        /// <summary>
        /// Get a list of all the threads under management
        /// </summary>
        /// <returns></returns>
        List<IThread> GetThreads();

        /// <summary>
        /// Start all threads running
        /// </summary>
        void StartAllThreads();

        /// <summary>
        /// Stop all threads
        /// </summary>
        void StopAllThreads();

        /// <summary>
        /// Removes all threads from the manager
        /// </summary>
        void ClearAllThreads();

        /// <summary>
        /// Send a message to the thread that created the Thread Manager
        /// </summary>
        /// <param name="msg"></param>
        void SendMessage(BaseMessage msg);

        /// <summary>
        /// If your application code wants to receive messages,
        /// it should wire in this event.
        /// </summary>
        event Action<BaseMessage> ReceivedMessage;
    }
}
