//
// 
//

#include "host.h"
#include "modules.h"
#include "DirectX12/LucusD3D12RenderSystem.h"

#include <ppltasks.h>

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

using Microsoft::WRL::ComPtr;



namespace LucusEngine
{
	// Main entry point for our app. Connects the app with the Windows shell and handles application lifecycle events.
	ref class ViewProvider sealed : public IFrameworkView
	{
	public:
		ViewProvider() :
            m_windowClosed(false),
            m_windowVisible(true)
        {
            //
        }

		// IFrameworkView methods.
		virtual void Initialize(CoreApplicationView^ applicationView)
        {
            // Register event handlers for app lifecycle. This example includes Activated, so that we
            // can make the CoreWindow active and start rendering on the window.
            applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &ViewProvider::OnActivated);

            CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &ViewProvider::OnSuspending);

            CoreApplication::Resuming += ref new EventHandler<Platform::Object^>(this, &ViewProvider::OnResuming);

            AKUCoreCreate();
			AKUModulesCreate();

			AKUChangeWorkingDir("Assets");

            D3D12RenderSystem* renderSystem = new D3D12RenderSystem();
            m_renderSystem = renderSystem;

            AKUSetRenderSystem(static_cast<RenderSystem*>(renderSystem));
        }

		virtual void SetWindow(CoreWindow^ window)
        {
            window->SizeChanged += ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &ViewProvider::OnWindowSizeChanged);

            window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &ViewProvider::OnVisibilityChanged);

            window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &ViewProvider::OnWindowClosed);

            DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

            currentDisplayInformation->DpiChanged += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &ViewProvider::OnDpiChanged);

            currentDisplayInformation->OrientationChanged += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &ViewProvider::OnOrientationChanged);

            DisplayInformation::DisplayContentsInvalidated += ref new TypedEventHandler<DisplayInformation^, Object^>(this, &ViewProvider::OnDisplayContentsInvalidated);

			//window->
            
			if (m_renderSystem)
			{
				m_renderSystem->SetCoreWindow(window);
			}
        }

		virtual void Load(Platform::String^ entryPoint)
        {
        }

		virtual void Run()
        {
            while (!m_windowClosed)
            {
                if (m_windowVisible)
                {
                    CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

					AKUTick();

                    // auto commandQueue = GetDeviceResources()->GetCommandQueue();
                    // PIXBeginEvent(commandQueue, 0, L"Update");
                    // {
                    // 	m_main->Update();
                    // }
                    // PIXEndEvent(commandQueue);

                    // PIXBeginEvent(commandQueue, 0, L"Render");
                    // {
                    // 	if (m_main->Render())
                    // 	{
                    // 		GetDeviceResources()->Present();
                    // 	}
                    // }
                    // PIXEndEvent(commandQueue);
                }
                else
                {
                    CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
                }
            }
        }

		virtual void Uninitialize()
        {
			m_renderSystem = nullptr;

            AKUCoreDestroy();
        }

	protected:
		// Application lifecycle event handlers.
		void OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
        {
            // Run() won't start until the CoreWindow is activated.
            CoreWindow::GetForCurrentThread()->Activate();
        }

		void OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
        {
            // Save app state asynchronously after requesting a deferral. Holding a deferral
            // indicates that the application is busy performing suspending operations. Be
            // aware that a deferral may not be held indefinitely. After about five seconds,
            // the app will be forced to exit.
            SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

            create_task([this, deferral]()
            {
                // m_main->OnSuspending();
                deferral->Complete();
            });
        }

		void OnResuming(Platform::Object^ sender, Platform::Object^ args)
        {
            // Restore any data or state that was unloaded on suspend. By default, data
            // and state are persisted when resuming from suspend. Note that this event
            // does not occur if the app was previously terminated.

            // m_main->OnResuming();
        }

		// Window event handlers.
		void OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
        {
            // GetDeviceResources()->SetLogicalSize(Size(sender->Bounds.Width, sender->Bounds.Height));
            // m_main->OnWindowSizeChanged();
			AKUChangeViewportSize(static_cast<u32>(sender->Bounds.Width), static_cast<u32>(sender->Bounds.Height));
        }

		void OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
        {
            m_windowVisible = args->Visible;
        }

		void OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
        {
            m_windowClosed = true;
        }

		// DisplayInformation event handlers.
		void OnDpiChanged(DisplayInformation^ sender, Platform::Object^ args)
        {
            // Note: The value for LogicalDpi retrieved here may not match the effective DPI of the app
            // if it is being scaled for high resolution devices. Once the DPI is set on DeviceResources,
            // you should always retrieve it using the GetDpi method.
            // See DeviceResources.cpp for more details.
            // GetDeviceResources()->SetDpi(sender->LogicalDpi);
            // m_main->OnWindowSizeChanged();
        }

		void OnOrientationChanged(DisplayInformation^ sender, Platform::Object^ args)
        {
            // GetDeviceResources()->SetCurrentOrientation(sender->CurrentOrientation);
            // m_main->OnWindowSizeChanged();
        }

		void OnDisplayContentsInvalidated(DisplayInformation^ sender, Platform::Object^ args)
        {
            // GetDeviceResources()->ValidateDevice();
        }

	private:
		// Private accessor for m_deviceResources, protects against device removed errors.
		// std::shared_ptr<DeviceResources> GetDeviceResources()
//         {
// 	if (m_deviceResources != nullptr && m_deviceResources->IsDeviceRemoved())
// 	{
// 		// All references to the existing D3D device must be released before a new device
// 		// can be created.

// 		m_deviceResources = nullptr;
// // 		m_main->OnDeviceRemoved();

// // #if defined(_DEBUG)
// // 		ComPtr<IDXGIDebug1> dxgiDebug;
// // 		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug))))
// // 		{
// // 			dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_SUMMARY | DXGI_DEBUG_RLO_IGNORE_INTERNAL));
// // 		}
// // #endif
// 	}

// 	if (m_deviceResources == nullptr)
// 	{
// 		m_deviceResources = std::make_shared<DeviceResources>();
// 		m_deviceResources->SetWindow(CoreWindow::GetForCurrentThread());
// 		// m_main->CreateRenderers(m_deviceResources);
// 	}
// 	return m_deviceResources;
// }

        LucusEngine::D3D12RenderSystem* m_renderSystem;

		bool m_windowClosed;
		bool m_windowVisible;
	};

    ref class ViewProviderFactory sealed : IFrameworkViewSource
    {
    public:
        virtual IFrameworkView^ CreateView()
        {
            return ref new ViewProvider();
        }
    };
}

// The main function is only used to initialize our IFrameworkView class.
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto viewProviderFactory = ref new LucusEngine::ViewProviderFactory();
	CoreApplication::Run(viewProviderFactory);
	return 0;
}