using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ThreadMessaging.Messages;

namespace ThreadMessaging
{
    /// <summary>
    /// Interface to a managed thread object
    /// </summary>
    public interface IThread
    {
        /// <summary>
        /// The thread name
        /// </summary>
        string Name { get; }

        /// <summary>
        /// Start this thread running
        /// </summary>
        void StartThread();

        /// <summary>
        /// Stop this thread
        /// </summary>
        void StopThread();

        /// <summary>
        /// Send a message to this thread
        /// </summary>
        /// <param name="msg"></param>
        void SendMessage(BaseMessage msg);
    }
}
