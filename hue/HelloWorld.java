// import com.philips.lighting.data.AccessPointListAdapter;
// import com.philips.lighting.data.HueSharedPreferences;

import com.philips.lighting.hue.sdk.PHAccessPoint;
import com.philips.lighting.hue.sdk.PHBridgeSearchManager;
import com.philips.lighting.hue.sdk.PHHueSDK;
import com.philips.lighting.hue.sdk.PHMessageType;
import com.philips.lighting.hue.sdk.PHSDKListener;
import com.philips.lighting.model.PHBridge;
import com.philips.lighting.model.PHHueError;
import java.util.List;

public class HelloWorld {
    static PHHueSDK phHueSDK;

    public static void main(String[] args) {
        System.out.println("Hello, World");

        // Gets an instance of the Hue SDK.
        phHueSDK = PHHueSDK.create();
        
        // Set the Device Name (name of your app). This will be stored in your bridge whitelist entry.
        phHueSDK.setDeviceName("QuickStartApp");

        // Local SDK Listener
        PHSDKListener listener = new PHSDKListener() {
                @Override
                    public void onAccessPointsFound(List<PHAccessPoint> accessPoint) {
//                    Log.w(TAG, "Access Points Found. " + accessPoint.size());
//
//                    PHWizardAlertDialog.getInstance().closeProgressDialog();
//                    if (accessPoint != null && accessPoint.size() > 0) {
//                        phHueSDK.getAccessPointsFound().clear();
//                        phHueSDK.getAccessPointsFound().addAll(accessPoint);
//
//                        runOnUiThread(new Runnable() {
//                                @Override
//                                    public void run() {
//                                    adapter.updateData(phHueSDK.getAccessPointsFound());
//                                }
//                            });
//                   
//                    } 
            
                }
        
                @Override
                    public void onCacheUpdated(int flags, PHBridge bridge) {
            //                    Log.w(TAG, "On CacheUpdated");

                }

                @Override
                    public void onBridgeConnected(PHBridge b) {
                    phHueSDK.setSelectedBridge(b);
                    phHueSDK.enableHeartbeat(b, PHHueSDK.HB_INTERVAL);
//                    phHueSDK.getLastHeartbeat().put(b.getResourceCache().getBridgeConfiguration() .getIpAddress(), System.currentTimeMillis());
//                    prefs.setLastConnectedIPAddress(b.getResourceCache().getBridgeConfiguration().getIpAddress());
//                    prefs.setUsername(prefs.getUsername());
//                    PHWizardAlertDialog.getInstance().closeProgressDialog();     
//                    startMainActivity();
                }

                @Override
                    public void onAuthenticationRequired(PHAccessPoint accessPoint) {
//                    Log.w(TAG, "Authentication Required.");
//                    phHueSDK.startPushlinkAuthentication(accessPoint);
//                    startActivity(new Intent(PHHomeActivity.this, PHPushlinkActivity.class));
           
                }

                @Override
                    public void onConnectionResumed(PHBridge bridge) {
//                    if (PHHomeActivity.this.isFinishing())
//                        return;
//            
//                    Log.v(TAG, "onConnectionResumed" + bridge.getResourceCache().getBridgeConfiguration().getIpAddress());
//                    phHueSDK.getLastHeartbeat().put(bridge.getResourceCache().getBridgeConfiguration().getIpAddress(),  System.currentTimeMillis());
//                    for (int i = 0; i < phHueSDK.getDisconnectedAccessPoint().size(); i++) {
//
//                        if (phHueSDK.getDisconnectedAccessPoint().get(i).getIpAddress().equals(bridge.getResourceCache().getBridgeConfiguration().getIpAddress())) {
//                            phHueSDK.getDisconnectedAccessPoint().remove(i);
//                        }
//                    }

                }

                @Override
                    public void onConnectionLost(PHAccessPoint accessPoint) {
                    //                    Log.v(TAG, "onConnectionLost : " + accessPoint.getIpAddress());
                    //                    if (!phHueSDK.getDisconnectedAccessPoint().contains(accessPoint)) {
                    //                        phHueSDK.getDisconnectedAccessPoint().add(accessPoint);
                    //                    }
                }
        
                @Override
                    public void onError(int code, final String message) {
//                    Log.e(TAG, "on Error Called : " + code + ":" + message);
//
//                    if (code == PHHueError.NO_CONNECTION) {
//                        Log.w(TAG, "On No Connection");
//                    } 
//                    else if (code == PHHueError.AUTHENTICATION_FAILED || code==1158) {  
//                        PHWizardAlertDialog.getInstance().closeProgressDialog();
//                    } 
//                    else if (code == PHHueError.BRIDGE_NOT_RESPONDING) {
//                        Log.w(TAG, "Bridge Not Responding . . . ");
//                        PHWizardAlertDialog.getInstance().closeProgressDialog();
//                        PHHomeActivity.this.runOnUiThread(new Runnable() {
//                                @Override
//                                    public void run() {
//                                    PHWizardAlertDialog.showErrorDialog(PHHomeActivity.this, message, R.string.btn_ok);
//                                }
//                            }); 
//
//                    } 
//                    else if (code == PHMessageType.BRIDGE_NOT_FOUND) {
//
//                        if (!lastSearchWasIPScan) {  // Perform an IP Scan (backup mechanism) if UPNP and Portal Search fails.
//                            phHueSDK = PHHueSDK.getInstance();
//                            PHBridgeSearchManager sm = (PHBridgeSearchManager) phHueSDK.getSDKService(PHHueSDK.SEARCH_BRIDGE);
//                            sm.search(false, false, true);               
//                            lastSearchWasIPScan=true;
//                        }
//                        else {
//                            PHWizardAlertDialog.getInstance().closeProgressDialog();
//                            PHHomeActivity.this.runOnUiThread(new Runnable() {
//                                    @Override
//                                        public void run() {
//                                        PHWizardAlertDialog.showErrorDialog(PHHomeActivity.this, message, R.string.btn_ok);
//                                    }
//                                });  
//                        }
//                
//               
//                    }
//                }
                }
            };
        
        // Register the PHSDKListener to receive callbacks from the bridge.
        phHueSDK.getNotificationManager().registerSDKListener(listener);
    }
}

